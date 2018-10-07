const express = require('express');
const mqtt = require('mqtt');
const mosca = require('mosca');
const bodyParser = require('body-parser');

const app = express();
app.use(bodyParser.json());

const mqtt_server = new mosca.Server({
    port: 1883
});

mqtt_server.on('clientConnected', (client) => console.log(`Client ${client.id} connected`));
mqtt_server.on('ready', () => console.log('Server ready'));

const client = mqtt.connect({ clientId: "mqtt-local-client" });

client.on('connect', () => {
    client.subscribe('home', (err) => {
        console.log(`Connected to localhost and subscribed to \"home\" with ${err ? 'error' : 'no error'}`);
    });
});

client.on('message', (topic, message) => {
    console.log(`Incoming MQTT packet`);
    console.log(`topic: ${topic}`);
    console.log(`message: ${message}`);
});

app.post('/', (req, res) => {
    var topic = req.body.topic.toString();
    var message = req.body.message.toString();
    client.publish(topic, message, (err) => {
        if (err) res.json({ status: 'ERROR' });
        else {
            res.json({
                status: 'OK',
                topic: topic,
                message: message
            });
        }
    });
});

app.listen(8000);
console.log('Listening to port 8000');