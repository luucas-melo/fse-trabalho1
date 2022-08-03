import type { AppProps } from 'next/app'
import { theme } from '@/styles/theme'
import '@/styles/globals.css'
import { ChakraProvider, CSSReset } from '@chakra-ui/react'
import { TrafficLightProvider } from 'Context/TrafficLightContext'

function MyApp({ Component, pageProps }: AppProps) {
  return (
    <TrafficLightProvider>
      <ChakraProvider theme={theme}>
        <CSSReset />
        <Component {...pageProps} />
      </ChakraProvider>
    </TrafficLightProvider>
  )
}

export default MyApp
