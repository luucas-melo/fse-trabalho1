import type { NextPage } from 'next';
import Head from 'next/head';
import Image from 'next/image';
import { useSocket } from '../hooks/useSocket';
import styles from '../styles/Home.module.css';

const Home: NextPage = () => {
  const socket = useSocket();
  return <div className={styles.container}>TESTE</div>;
};

export default Home;
