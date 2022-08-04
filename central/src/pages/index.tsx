import { CrossingContainer } from '@/components/CrossingContainer'

import { Badge, Box, Flex, Grid } from '@chakra-ui/react'
import { useTrafficLight } from 'Context/TrafficLightContext'
import { cloneDeep } from 'lodash'
import type { NextPage } from 'next'

import { useCallback, useEffect, useState } from 'react'
import { Navbar } from '../components'
import { useSocket } from '../hooks/useSocket'
const Home: NextPage = () => {
  const { crossings, setCrossings, socket } = useTrafficLight()
  useEffect(() => {
    console.log('CAAAA', socket)
    if (!socket) return
    console.log('use effect')

    socket?.on('CONNECTION', (msg: ServerMessage) => {
      console.log('connection')
      const connected = !!Number(msg?.message)
      console.log(connected)
      crossings[msg?.host] = 'standardMode'

      const newCrossings = cloneDeep(crossings)
      if (connected) setCrossings(newCrossings)
    })
  }, [socket])

  console.log('connecteds', crossings)

  return (
    <Box minH="100vh" padding="2rem">
      <Navbar />

      <Grid
        templateColumns={'repeat(auto-fill, minmax(250px, 1fr))'}
        gap="4rem"
        autoFlow="row dense"
        justifyItems="center"
      >
        {Object.keys(crossings).map((crossingName) => {
          return <CrossingContainer crossingName={crossingName} />
        })}
      </Grid>
    </Box>
  )
}

export default Home
