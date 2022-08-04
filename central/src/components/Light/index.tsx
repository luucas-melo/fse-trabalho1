import { Box } from '@chakra-ui/react'
import { CSSProperties } from 'react'

const colorMap = {
  red: 'red.500',
  yellow: 'yellow.500',
  green: 'green.500'
}
export const Light = ({
  color,
  style
}: {
  color: lightColor
  style?: CSSProperties
}) => {
  return (
    <Box
      className={color}
      width={14}
      height={14}
      borderRadius="50%"
      bg={colorMap[color]}
      style={style}
    />
  )
}
