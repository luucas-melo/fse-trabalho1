export const messageConverter = (message: Buffer): ServerMessage => {
  return JSON.parse(message.toString()) as ServerMessage;
};
