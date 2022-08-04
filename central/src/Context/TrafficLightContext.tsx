/* eslint-disable @typescript-eslint/no-empty-function */
import { useSocket } from '@/hooks/useSocket'
import React, { createContext, useContext, useMemo, useState } from 'react'
import { Socket } from 'socket.io-client'
import { DefaultEventsMap } from 'socket.io/dist/typed-events'

export type TrafficLightContextType = {
  crossings: Record<string, lightModes>
  setCrossings: React.Dispatch<React.SetStateAction<Record<string, lightModes>>>
  selectedCrossing: string
  setSelectedCrossing: React.Dispatch<React.SetStateAction<string>>
  selectedMode: string
  setSelectedMode: React.Dispatch<React.SetStateAction<lightModes>>
  socket: Socket<DefaultEventsMap, DefaultEventsMap> | null
}

export const TrafficLightContextDefaultValues: TrafficLightContextType = {
  crossings: {},
  setCrossings: () => {},
  selectedCrossing: '',
  setSelectedCrossing: () => {},
  selectedMode: '',
  setSelectedMode: () => {},
  socket: null
}

export const TrafficLightContext = createContext<any>(
  TrafficLightContextDefaultValues
)
TrafficLightContext.displayName = 'TrafficLightContext'

export const TrafficLightProvider: React.FC<any> = ({ children }) => {
  const [crossings, setCrossings] = useState({})
  const [selectedCrossing, setSelectedCrossing] = useState('')
  const [selectedMode, setSelectedMode] = useState<lightModes>('standardMode')
  const socket = useSocket()

  const values = useMemo(
    () => ({
      selectedCrossing,
      setSelectedCrossing,
      crossings,
      setCrossings,
      selectedMode,
      setSelectedMode,
      socket
    }),
    [selectedCrossing, crossings, socket, selectedMode]
  )

  return (
    <TrafficLightContext.Provider value={values}>
      {children}
    </TrafficLightContext.Provider>
  )
}

export function useTrafficLight() {
  const context = useContext<TrafficLightContextType>(TrafficLightContext)

  if (!context) {
    throw new Error(
      'useTrafficLight must be used within a TrafficLightProvider'
    )
  }

  return context
}
