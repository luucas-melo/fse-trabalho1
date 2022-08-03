import { Flex } from '@chakra-ui/react'
import { ColorModeSwitcher } from './ColorModeSwitcher'
export const Navbar = () => {
  return (
    <Flex marginBottom="20" width="100%" justifyContent="flex-end">
      <ColorModeSwitcher />
    </Flex>
  )
}
