import { Flex, IconButton, Tooltip } from '@chakra-ui/react'
import { useTrafficLight } from 'Context/TrafficLightContext'
import { useCallback, useEffect, useState } from 'react'
import { MdNightlight, MdPriorityHigh } from 'react-icons/md'
import { TbTrafficLights } from 'react-icons/tb'

export const Actions = () => {
  const { socket, crossings, setSelectedMode, selectedMode } = useTrafficLight()

  useEffect(() => {
    setSelectedMode('standardMode')
  }, [crossings])
  const setStandardMode = useCallback(() => {
    {
      Object.keys(crossings)?.map((crossing) => {
        socket?.emit('SEND_MESSAGE', {
          host: crossing,
          type: 'standardMode',
          message: 'on'
        })
      })
    }
    setSelectedMode('standardMode')
  }, [socket, crossings])
  const setNightMode = useCallback(() => {
    {
      Object.keys(crossings)?.map((crossing) => {
        socket?.emit('SEND_MESSAGE', {
          host: crossing,
          type: 'nightMode',
          message: 'on'
        })
      })
    }
    setSelectedMode('nightMode')
  }, [socket, crossings])

  const setEmergencyMode = useCallback(() => {
    Object.keys(crossings)?.map((crossing) => {
      socket?.emit('SEND_MESSAGE', {
        host: crossing,
        type: 'emergencyMode',
        message: 'on'
      })
    })
    setSelectedMode('emergencyMode')
  }, [socket, crossings])
  return (
    <Flex align="flex-end" gap="2rem" justifySelf="flex-end" height="100%">
      <Tooltip label="Fluxo normal" fontSize="md">
        <IconButton
          variant={selectedMode == 'standardMode' ? 'solid' : 'outline'}
          colorScheme="teal"
          aria-label="Call Sage"
          fontSize="20px"
          icon={<TbTrafficLights />}
          onClick={() => setStandardMode()}
        />
      </Tooltip>
      <Tooltip label="Modo noturno" fontSize="md">
        <IconButton
          variant={selectedMode == 'nightMode' ? 'solid' : 'outline'}
          colorScheme="teal"
          aria-label="Call Sage"
          fontSize="20px"
          icon={<MdNightlight />}
          onClick={() => setNightMode()}
        />
      </Tooltip>
      <Tooltip label="Modo de emergência" fontSize="md">
        <IconButton
          variant={selectedMode == 'emergencyMode' ? 'solid' : 'outline'}
          colorScheme="teal"
          aria-label="Call Sage"
          fontSize="20px"
          icon={<MdPriorityHigh />}
          onClick={() => setEmergencyMode()}
        />
      </Tooltip>
    </Flex>
  )
}
