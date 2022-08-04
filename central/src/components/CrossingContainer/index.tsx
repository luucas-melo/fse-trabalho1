import { Badge, Box, Flex, Heading, Text } from '@chakra-ui/react'
import { useTrafficLight } from 'Context/TrafficLightContext'
import { Actions } from '../Actions'
import { TrafficLightContainer } from '../TrafficLightContainer'

interface CrossingContainer {
  crossingName: string
}
export const CrossingContainer = ({ crossingName }: CrossingContainer) => {
  const { selectedCrossing, setSelectedCrossing } = useTrafficLight()

  console.log('SELECT', selectedCrossing)
  return (
    <Flex flexDirection="column">
      <Flex
        textTransform="capitalize"
        flexDirection="column"
        width="100%"
        align="center"
      >
        <Text fontWeight="light">{crossingName}</Text>
      </Flex>
      <Flex
        position="relative"
        flexDirection="column"
        align="center"
        justify="center"
        width="300px"
        height="300px"
        boxShadow="xl"
        bg="blackAlpha.900"
        fontStyle="capitalize"
        padding="1rem"
        borderRadius="10px"
        onClick={() => setSelectedCrossing(crossingName)}
        border={selectedCrossing === crossingName && '2px solid'}
        _hover={{
          boxShadow:
            'rgba(0, 0, 0, 0.25) 0px 54px 55px, rgba(0, 0, 0, 0.12) 0px -12px 30px, rgba(0, 0, 0, 0.12) 0px 4px 6px, rgba(0, 0, 0, 0.17) 0px 12px 13px, rgba(0, 0, 0, 0.09) 0px -3px 5px'
        }}
        borderColor="teal"
        cursor="pointer"
      >
        <TrafficLightContainer />

        <Flex
          className="glass"
          height="100%"
          width="100%"
          position="absolute"
        />
        <Actions />
      </Flex>
    </Flex>
  )
}
