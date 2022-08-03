import { Flex, IconButton, Tooltip } from '@chakra-ui/react'
import { MdNightlight, MdPriorityHigh } from 'react-icons/md'
import { TbTrafficLights } from 'react-icons/tb'

export const Actions = () => {
  return (
    <Flex align="flex-end" gap="2rem" justifySelf="flex-end" height="100%">
      <Tooltip label="Fluxo normal" fontSize="md">
        <IconButton
          variant="outline"
          colorScheme="facebook"
          aria-label="Call Sage"
          fontSize="20px"
          icon={<TbTrafficLights />}
        />
      </Tooltip>
      <Tooltip label="Modo noturno" fontSize="md">
        <IconButton
          variant="outline"
          colorScheme="facebook"
          aria-label="Call Sage"
          fontSize="20px"
          icon={<MdNightlight />}
        />
      </Tooltip>
      <Tooltip label="Modo de emergência" fontSize="md">
        <IconButton
          variant="outline"
          colorScheme="facebook"
          aria-label="Call Sage"
          fontSize="20px"
          icon={<MdPriorityHigh />}
        />
      </Tooltip>
    </Flex>
  )
}
