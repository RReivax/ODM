var http = require('http');
var net = require('net');
var express = require('express');
var path = require('path');
var variable = "";
var numberConnected = 0; 

var app = express();

var applicationServer = net.createServer(function(socket){
	console.log('server connected');
	socket.on('data', function(data) {
		console.log(data.toString('utf8'));
        variable = data.toString('utf8');
    });
});

app.use(express.static(__dirname + '/style'));
app.use(express.static(__dirname+'/leaflet'));
/* Displays index.html */
app.get('/',function(req,res){
	res.sendFile(__dirname + '/index.html');
});

/*Loads socket.io */
var io = require('socket.io').listen(app.listen(8080));


io.sockets.on('connection', function (socket) {
	numberConnected ++;
    console.log('Un client est connecté !');
	socket.emit('idUser',numberConnected);
	socket.emit('message', variable);
	setInterval(function(){
    	socket.emit('message', variable); 
	}, 100);
});

applicationServer.listen(7070);
