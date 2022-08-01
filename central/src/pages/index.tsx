import type { NextPage } from 'next';
import Head from 'next/head';
import Image from 'next/image';
import { useCallback, useEffect, useState } from 'react';
import { useSocket } from '../hooks/useSocket';
import styles from '../styles/Home.module.css';
const Home: NextPage = () => {
  const socket = useSocket();

  console.log('EL SOCKET', socket);
  const sendMessage = useCallback(() => {
    socket?.current.emit('EVENTO', { host: 'cruzamento 1', type: 'check', message: 'teste' });

    if (socket) {
      console.log('SOCKET ON', socket);
    }
  }, []);
  return (
    <div>
      <div className={styles.container}>TESTE</div>
      <button onClick={() => sendMessage()}> SEND MESSAGE</button>
    </div>
  );
};

export default Home;
