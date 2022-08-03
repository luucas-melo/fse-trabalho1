import fs from 'fs'
import net from 'net'

import { NextApiRequest, NextApiResponse } from 'next'
import { Server } from 'socket.io'
import { DefaultEventsMap } from 'socket.io/dist/typed-events'
import { messageConverter } from '@/utils/messageConverter'

interface ExtendedNextApiResponse<T = any> extends NextApiResponse<T> {
  server: net.Server
  socket:
    | (net.Socket & {
        server: {
          io: Server<DefaultEventsMap, DefaultEventsMap, DefaultEventsMap, any>
        }
      })
    | null
}

const connectedSockets: Record<string, net.Socket> = {}

const SocketHandler = (req: NextApiRequest, res: ExtendedNextApiResponse) => {
  //   console.log('RES', res?.socket?.server?.io);

  switch (req.method) {
    case 'GET': {
      if (!res?.socket?.server?.io) {
        console.log('Starting Socket.io')
        const io = new Server(res?.socket?.server)

        // @ts-ignore
        res.socket.server.io = io

        io.on('connection', (socket) => {
          console.log('RODOU CONNECTION')
          socket.on('SEND_MESSAGE', (data: ServerMessage) => {
            console.log('DATA', data)
            const { host, type, message } = data

            connectedSockets?.[host]?.write?.(
              JSON.stringify({
                type,
                message
              })
            )
          })
        })

        console.log(process.env.NODE_ENV)
        const server = net.createServer()

        server.on('error', (e) => {
          console.log('ERRO', e)
          if (e?.code === 'EADDRNOTAVAIL') {
            console.log('Address not available, retrying...')
            setTimeout(() => {
              server.close()
              server.listen(10292, 'localhost', () => {
                console.log('Socket listening on port localhost:10292')
              })
            }, 1000)
          }
        })

        server?.listen(10292, 'localhost', () => {
          console.log('Socket listening on port 10292')
        })

        server?.on('connection', (connection) => {
          connection.on('data', function (data) {
            const convertedMessage = messageConverter(data)

            switch (convertedMessage.type) {
              case 'connectionId':
                {
                  connectedSockets[convertedMessage.host] = connection
                  console.log('CONECTADO TESTE')
                  io.emit('CONNECTION', {
                    host: convertedMessage.host,
                    type: 'connection',
                    message: 1
                  })
                }
                console.log('DATA', messageConverter(data))
              case 'nightMode': {
                io.emit('NIGHT_MODE', {
                  host: convertedMessage.host,
                  type: 'nightMode',
                  message: 1
                })
              }
            }
          })

          connection.on('end', function () {
            Object.keys(connectedSockets).forEach((socket) => {
              if (connectedSockets[socket] === connection) {
                console.log(`${socket} disconnected`)
                io.emit('CONNECTION', {
                  from: socket,
                  type: 'connection',
                  value: 0
                })
                delete connectedSockets[socket]
              }
            })
          })
        })
      } else {
        console.log('Socket.io already running')
      }

      break
    }

    default: {
      break
    }
  }

  res.end()
}

export default SocketHandler
