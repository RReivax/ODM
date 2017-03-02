var http = require('http');
var net = require('net');
var express = require('express');
var path = require('path');
var variable = {'id':0,'latitude':48.8516,'longitude':2.28716};
var app = express();

console.log(variable);

var applicationServer = net.createServer(function(socket){
	console.log('server connected');
	socket.on('data', function(data) {
        variable = data;
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
	socket.emit('update', variable);
	setInterval(function(){
    	socket.emit('update', variable); 
	}, 100);
});

applicationServer.listen(7070);
