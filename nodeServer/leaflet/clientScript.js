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

