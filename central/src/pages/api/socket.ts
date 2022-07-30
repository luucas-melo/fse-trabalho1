import fs from 'fs';
import net from 'net';

import { NextApiRequest, NextApiResponse } from 'next';
import { Server } from 'socket.io';
import { DefaultEventsMap } from 'socket.io/dist/typed-events';

interface ExtendedNextApiResponse<T = any> extends NextApiResponse<T> {
  server: net.Server;
  socket:
    | (net.Socket & {
        server: {
          io: Server<DefaultEventsMap, DefaultEventsMap, DefaultEventsMap, any>;
        };
      })
    | null;
}

const connectedSockets: Record<string, net.Socket> = {};

const SocketHandler = (req: NextApiRequest, res: ExtendedNextApiResponse) => {
  switch (req.method) {
    case 'GET': {
      if (!res?.socket?.server?.io) {
        try {
          console.log('done');
        } catch (error) {
          console.error(error);
        }

        console.log('Starting Socket.io');
        const io = new Server(res?.socket?.server);

        io.on('connection', (socket) => {
          console.log('CONNECTED');
        });

        // @ts-ignore
        res.socket.server.io = io;

        console.log(process.env.NODE_ENV);
        const server = net.createServer();

        server.on('error', (e) => {
          console.log('ERRO', e);
          if (e?.code === 'EADDRNOTAVAIL') {
            console.log('Address not available, retrying...');
            setTimeout(() => {
              server.close();
              server.listen(10292, 'localhost', () => {
                console.log('Socket listening on port localhost:10292');
              });
            }, 1000);
          }
        });

        server?.listen(10292, process.env.NODE_ENV === 'development' ? 'localhost' : '192.168.0.53', () => {
          console.log('Socket listening on port 10292');
        });

        server?.on('connection', (connection) => {
          connection.on('data', function (data) {
            console.log('MESSAGE', data.toString());
          });

          connection.on('end', function () {
            Object.keys(connectedSockets).forEach((socket) => {
              if (connectedSockets[socket] === connection) {
                console.log(`${socket} disconnected`);
                io.emit('connection', {
                  from: socket,
                  type: 'connection',
                  value: 0,
                });
                delete connectedSockets[socket];
              }
            });
          });
        });
      } else {
        console.log('Socket.io already running');
      }

      break;
    }

    default: {
      break;
    }
  }

  res.end();
};

export default SocketHandler;
