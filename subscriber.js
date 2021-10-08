const mqtt = require('mqtt');
const client = mqtt.connect("mqtt://broker.hivemq.com:1883");

client.on('connect', () => {
  client.subscribe('/DarkArts/messages');
  console.log('mqtt connected');
});

client.on('message', (topic, message) => {
  console.log(`Received message on ${topic}: ${message}`);
});

client.on('message', (topic, message) => {
  if (topic == '/DarkArts/messages') {
    msg = `${message}`;
    console.log(msg);
  }
});