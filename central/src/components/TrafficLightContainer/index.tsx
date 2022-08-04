import { Flex } from '@chakra-ui/react'
import { useTrafficLight } from 'Context/TrafficLightContext'
import { Light } from '../Light'

export const TrafficLightContainer = () => {
  const { selectedMode } = useTrafficLight()
  return (
    <Flex
      height="100%"
      width="100%"
      flexDirection="column"
      gap="2rem"
      justify="center"
      align="center"
      padding="1rem"
      position="absolute"
    >
      {
        {
          standardMode: (
            <>
              <Light color="red" />
              <Light color="yellow" />
              <Light color="green" />
            </>
          ),
          emergencyMode: (
            <>
              <Light color="red" style={{ animation: '0s', opacity: 1 }} />
              <Light color="yellow" style={{ animation: '0s', opacity: 0.2 }} />
              <Light
                color="green"
                style={{ animationDuration: '0s', opacity: 1 }}
              />
            </>
          ),
          nightMode: (
            <>
              <Light color="red" style={{ animation: '0s', opacity: 0.2 }} />
              <Light
                color="yellow"
                style={{ animationDuration: '2s', opacity: 0.2 }}
              />
              <Light color="green" style={{ animation: '0s', opacity: 0.2 }} />
            </>
          )
        }[selectedMode]
      }
    </Flex>
  )
}
