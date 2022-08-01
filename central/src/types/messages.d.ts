interface ServerMessage {
  host: string;
  type: 'nightMode' | 'connectionId';
  message: string;
}
