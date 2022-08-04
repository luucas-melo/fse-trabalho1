/* eslint-disable @typescript-eslint/no-empty-function */
import React, { createContext, useContext, useMemo, useState } from 'react'

export type Data<T> = T
export type DataRecord = Record<string, lightModes>

export type TrafficLightContextType<T> = {
  crossings: Record<string, lightModes>
  setCrossings: React.Dispatch<React.SetStateAction<Record<string, lightModes>>>
  selectedCrossing: string
  setSelectedCrossing: React.Dispatch<React.SetStateAction<string>>
}

export const TrafficLightContextDefaultValues: TrafficLightContextType<DataRecord> =
  {
    crossings: {},
    setCrossings: () => {},

    selectedCrossing: '',
    setSelectedCrossing: () => {}
  }

export const TrafficLightContext = createContext<any>(
  TrafficLightContextDefaultValues
)
TrafficLightContext.displayName = 'TrafficLightContext'

export const TrafficLightProvider: React.FC<any> = ({ children }) => {
  const [crossings, setCrossings] = useState({})
  const [selectedCrossing, setSelectedCrossing] = useState('')

  const values = useMemo(
    () => ({
      selectedCrossing,
      setSelectedCrossing,
      crossings,
      setCrossings
    }),
    [selectedCrossing, crossings]
  )

  return (
    <TrafficLightContext.Provider value={values}>
      {children}
    </TrafficLightContext.Provider>
  )
}

export function useTrafficLight<T>() {
  const context = useContext<TrafficLightContextType<T>>(TrafficLightContext)

  if (!context) {
    throw new Error(
      'useTrafficLight must be used within a TrafficLightProvider'
    )
  }

  return context
}
