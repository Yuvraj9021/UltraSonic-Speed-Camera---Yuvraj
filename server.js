const express = require('express');
const http = require('http');
const socketIo = require('socket.io');

const app = express();
const server = http.createServer(app);
const io = socketIo(server);

app.use(express.static('public'));

io.on('connection', (socket) => {
    console.log('Client connected');

    socket.on('disconnect', () => {
        console.log('Client disconnected');
    });
});

const PORT = 3000;
server.listen(PORT, () => {
    console.log(`Server listening on port ${PORT}`);
});

app.post('/speed', express.raw({ type: '*/*' }), (req, res) => {
    console.log("Raw buffer received:", req.body);
    const speedStr = req.body.toString('utf8');
    const speed = parseFloat(speedStr);
    console.log("Parsed speed from ESP32:", speed);
    io.emit('speedUpdate', speed);
    res.sendStatus(200);
});

