var http = require('http');
var net = require('net');
var express = require('express');
var path = require('path');
var variable ="" ;
var app = express();


var applicationServer = net.createServer(function(socket){
	console.log('server connected');
	socket.on('data', function(data) {
	data = data + "";
	if(data.replace(/[^{]/g,"").length < 2)
				variable =data; 
				console.log("variable : "+variable+ " END");
				
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
	}, 20);
});

applicationServer.listen(7070);
