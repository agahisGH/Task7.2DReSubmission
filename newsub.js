const mqtt = require('mqtt');
const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');

const port = new SerialPort('COM5', { baudRate: 9600 });
const parser = port.pipe(new Readline({ delimiter: '\n' }));
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

client.on('message', (topic, message) => {
    if (topic == '/DarkArts/messages') {
      msg = `${message}\n`;
      console.log(msg);

      //now send it to the Arduino
      port.write(msg, (err) => {
        if (err) {
          return console.log('Error on write: ', err.message);
        }
        console.log('message written');
      });

    }
  });