interface ServerMessage {
  from: string;
  type: 'nightMode' | 'connectionId';
  value: string;
}
