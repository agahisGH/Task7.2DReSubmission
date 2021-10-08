const mqtt = require('mqtt');
const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');

const port = new SerialPort('COM5', { baudRate: 9600});
const parser = port.pipe(new Readline({ delimiter: '\n' }));
const client = mqtt.connect("mqtt://broker.hivemq.com:1883")

client.on('connect', () => {
    console.log('connected');
});

const topic = '/DarkArts/messages';
//const msg = 'Hello MQTT world!';

// Read the port data
port.on("open", () => {
    console.log('serial port one');
});

// Got a message from the Arduino
parser.on('data', data =>{
    console.log('got word from arduino:', data);
    client.publish(topic, data, () => {
        console.log('published the message to MQTT...');
    });
});