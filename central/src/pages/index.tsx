import { CrossingContainer } from '@/components/CrossingContainer'

import { Badge, Box, Flex } from '@chakra-ui/react'
import type { NextPage } from 'next'

import { useCallback, useEffect, useState } from 'react'
import { Navbar } from '../components'
import { useSocket } from '../hooks/useSocket'
const Home: NextPage = () => {
  const socket = useSocket()
  const [connecteds, setConnecteds] = useState({})

  useEffect(() => {
    console.log('CAAAA', socket)
    if (!socket) return
    console.log('use effect')

    socket?.on('CONNECTION', (msg: ServerMessage) => {
      console.log('connection')
      const connected = !!Number(msg?.type)

      setConnecteds({ ...connecteds, [msg?.host]: connected })
    })
  }, [socket])

  console.log('connecteds', connecteds)

  console.log('EL SOCKET', socket)
  const sendMessage = useCallback(() => {
    socket?.emit('SEND_MESSAGE', {
      host: 'cruzamento 2',
      type: 'nightMode',
      message: 'on'
    })

    if (socket) {
      console.log('SOCKET ON', socket)
    }
  }, [socket])
  return (
    <Box minH="100vh">
      <Navbar />

      <Flex flexDirection="column" alignItems="flex-start" padding="2rem">
        <CrossingContainer crossingName="cruzamento 1" />
        {/* <button onClick={() => sendMessage()}> SEND MESSAGE</button> */}
      </Flex>
    </Box>
  )
}

export default Home
