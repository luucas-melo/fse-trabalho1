import { useEffect, useState } from 'react'
import { DefaultEventsMap } from 'socket.io/dist/typed-events'
import { io, Socket } from 'socket.io-client'

export const useSocket = () => {
  const [socket, setSocket] = useState<Socket<
    DefaultEventsMap,
    DefaultEventsMap
  > | null>(null)

  useEffect(() => {
    const initSocket = async () => {
      await fetch('/api/socket')
      const socketIo = io()
      setSocket(socketIo)
    }

    initSocket()

    return () => {
      socket?.disconnect?.()
    }
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [])

  return socket
}
