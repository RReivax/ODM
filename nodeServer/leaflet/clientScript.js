/**
 *  * Copyright 2017 Gauthier Leonard, Xavier Hermand, Robin Dade, Oscar Blazejewski, Arnaud Petitcol
 *   * This file is part of Open Drone Monitoring.
 *    * Open Drone Monitoring is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 *     * Open Drone Monitoring is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 *      * You should have received a copy of the GNU Lesser General Public License along with Open Drone Monitoring. If not, see <http://www.gnu.org/licenses/>.
 *      */
var map;
var ajaxRequest;
var plotlist;
var plotlayers=[];
var marker;
var posMarker;
var droneIcon;
var drones= [];

function initmap() {
    // set up the map
	
    map = new L.Map('map');

	//position of our school
	posMarker = new L.LatLng(48.851658, 2.287161);
	droneIcon = L.icon({
			//Icon made by Freepik from www.flaticon.com 
		iconUrl: 'images/drone-icon.png',
		shadowUrl : 'images/drone-icon.png',
		iconSize : [32,32],
		shadowSize : [32,32],
		iconAnchor : [16,16],
		shadowAnchor : [16,16],
		popupAnchor: [-3,10]
	});

    // create the tile layer with correct attribution
    var osmUrl='http://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png';
    var osmAttrib='Map data © <a href="http://openstreetmap.org">OpenStreetMap</a> contributors';
    var osm = new L.TileLayer(osmUrl, {minZoom: 0, maxZoom: 18, attribution: osmAttrib});

    map.setView(posMarker,9);
	map.setZoom(18);
    map.addLayer(osm);

    var socket = io.connect('http://'+location.hostname+':8080');

		socket.on('update', function(message){
				message = JSON.parse(message);
				console.log(message);
			if(drones[message.name] === undefined){
					drones[message.name]= L.marker([message.Latitude,message.Longitude],{icon:droneIcon}).addTo(map);
			}
			else if(message.name != null && message.Latitude !=null && message.Longitude !=null){
				drones[message.name].setLatLng(new L.LatLng(message.Latitude,message.Longitude));
			}
			else console.log("Message not valid");
		});
}

