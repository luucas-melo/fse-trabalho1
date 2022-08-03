import { Flex } from '@chakra-ui/react'
import { Light } from '../Light'

export const TrafficLightContainer = () => {
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
      <Light color="red" />
      <Light color="yellow" />
      <Light color="green" />
    </Flex>
  )
}
