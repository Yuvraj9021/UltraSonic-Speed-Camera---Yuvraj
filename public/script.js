const socket = io.connect();
socket.on('speedUpdate', (speed) => {
    document.getElementById('speedDisplay').textContent = speed.toFixed(2);
});

socket.on('connect', () => {
    console.log('Connected to server via WebSockets');
});
