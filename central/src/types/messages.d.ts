interface ServerMessage {
  host: string
  type: 'nightMode' | 'connectionId' | 'emergencyMode'
  message: string
}
