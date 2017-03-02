var http = require('http');
var fs = require('fs');
var net = require('net');
var variable = "";
var numberConnected = 0; 

var serverQT = net.createServer(function(socket){
	console.log('client QT connected');
    	socket.on('data', function(data) {
	console.log(data.toString('utf8'));
        variable = data.toString('utf8');
    });
});

// Chargement du fichier index.html affiché au client
var server = http.createServer(function(req, res) {

    fs.readFile('./map.html', 'utf-8', function(error, content) {
        res.writeHead(200, {"Content-Type": "text/html"});
        res.end(content);
    });
});

// Chargement de socket.io
var io = require('socket.io').listen(server);

// Quand un client se connecte, on le note dans la console
io.sockets.on('connection', function (socket) {
	numberConnected ++;
    console.log('Un client est connecté !');
	socket.emit('idUser',numberConnected);
        socket.emit('message', variable);
setInterval(function(){
    socket.emit('message', variable); 
}, 1000);
});

serverQT.listen(7070);
server.listen(8080);
