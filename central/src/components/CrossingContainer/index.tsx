import { Badge, Box, Divider, Flex, Heading, Text } from '@chakra-ui/react'
import { useTrafficLight } from 'Context/TrafficLightContext'
import { Actions } from '../Actions'
import { TrafficLightContainer } from '../TrafficLightContainer'

export const CrossingContainer = () => {
  const { selectedCrossing, crossings } = useTrafficLight()

  console.log('SELECT', selectedCrossing)
  return (
    <Flex
      flexDirection="column"
      border={'1px solid'}
      borderColor="teal"
      borderRadius="10px"
      bg="blackAlpha.900"
      textTransform="capitalize"
      boxShadow="2xl"
    >
      {Object.keys(crossings)?.map((crossing) => {
        return (
          <Flex flexDirection="column" padding="1rem">
            <Text>{crossing}</Text>
            <Divider />
          </Flex>
        )
      })}
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
