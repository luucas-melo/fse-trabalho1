import { useCallback, useEffect, useRef, useState } from 'react';
import { DefaultEventsMap } from 'socket.io/dist/typed-events';
import { io, Socket } from 'socket.io-client';

export const useSocket = () => {
  const socket = useRef<Socket<DefaultEventsMap, DefaultEventsMap> | null>(null);

  const initSocker = useCallback(async () => {
    await fetch('/api/socket');
    socket.current = io();
    console.log('socket.current', socket.current);
  }, [socket]);
  useEffect(() => {
    initSocker();
    console.log('AAAA ');
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, []);
  useEffect(() => {
    console.log('socket', socket);
  }, [socket]);

  //   socket?.current?.on('EVENTO', (data) => {
  //     console.log('data', data);
  //   });
  return socket;
};
