/**
 *  * Copyright 2017 Gauthier Leonard, Xavier Hermand, Robin Dade, Oscar Blazejewski, Arnaud Petitcol
 *   * This file is part of Open Drone Monitoring.
 *    * Open Drone Monitoring is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 *     * Open Drone Monitoring is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 *      * You should have received a copy of the GNU Lesser General Public License along with Open Drone Monitoring. If not, see <http://www.gnu.org/licenses/>.
 *      */
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
