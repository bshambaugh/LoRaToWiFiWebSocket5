const WebSocket = require('ws');

const ws = new WebSocket('ws://10.0.0.5:8080');

ws.on('open', function open() {
  ws.send('Marko');
});

ws.on('message', function incoming(data) {
  console.log(data);
});
