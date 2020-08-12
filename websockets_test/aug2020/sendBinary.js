const WebSocket = require('ws');

const ws = new WebSocket('ws://10.0.0.5:8080');

ws.on('open', function open() {
  const array = new Float32Array(5);

  for (var i = 0; i < array.length; ++i) {
    array[i] = i / 2;
  }

  ws.send(array);
  ws.send('hello');
  ws.send('marko');
});
