import { CrossingContainer } from '@/components/CrossingContainer'

import { Box, Flex, Heading, Spinner } from '@chakra-ui/react'
import { useTrafficLight } from 'Context/TrafficLightContext'
import { cloneDeep } from 'lodash'
import type { NextPage } from 'next'

import { useEffect } from 'react'
const Home: NextPage = () => {
  const { crossings, setCrossings, socket } = useTrafficLight()
  useEffect(() => {
    console.log('CAAAA', socket)
    if (!socket) return
    console.log('use effect')

    socket?.on('CONNECTION', (msg: ServerMessage) => {
      console.log('connection', msg)
      const connected = !!Number(msg?.message)
      if (connected) {
        crossings[msg?.host] = 'standardMode'
      } else {
        console.log('else')
        delete crossings[msg?.host]
        console.log('novo', crossings)
      }
      const newCrossings = cloneDeep(crossings)

      setCrossings(newCrossings)
    })
  }, [socket])

  console.log('connecteds', crossings)

  if (Object.keys(crossings).length < 1)
    return (
      <Flex
        h="100vh"
        flexDirection="column"
        padding="2rem"
        justify="center"
        align="center"
      >
        <Box>
          <Spinner
            thickness="4px"
            speed="0.65s"
            emptyColor="gray.200"
            color="blue.500"
            size="xl"
          />
        </Box>
        <Heading fontSize="4xl" fontWeight="light">
          Esperando conexões...
        </Heading>
      </Flex>
    )
  return (
    <Flex minH="100vh" justify="center" align="center" padding="2rem">
      {/* <Grid
        templateColumns={'repeat(auto-fill, minmax(250px, 1fr))'}
        gap="4rem"
        autoFlow="row dense"
        justifyItems="center"
      > */}

      <CrossingContainer />

      {/* </Grid> */}
    </Flex>
  )
}

export default Home
