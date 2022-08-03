import { Badge, Flex, Heading, Text } from '@chakra-ui/react'
import { Actions } from '../Actions'
import { TrafficLightContainer } from '../TrafficLightContainer'

interface CrossingContainer {
  crossingName: string
}
export const CrossingContainer = ({ crossingName }: CrossingContainer) => {
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
        bg="gray.900"
        color="whiteAlpha.900"
        fontStyle="capitalize"
        padding="1rem"
        borderRadius="10px"
      >
        <TrafficLightContainer />
        <Flex
          className="glass"
          height="100%"
          width="100%"
          position="absolute"
        ></Flex>
        <Actions />
      </Flex>
    </Flex>
  )
}
