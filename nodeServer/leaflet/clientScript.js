var map;
var ajaxRequest;
var plotlist;
var plotlayers=[];
var marker;
var posMarker;
function moveMarker(){

	posMarker.lat = posMarker.lat - (Math.random()/100000);
	posMarker.lng = posMarker.lng - (Math.random()/100000);
	marker.setLatLng(posMarker);
}

function initmap() {
    // set up the map
    map = new L.Map('map');
posMarker = new L.LatLng(48.851658, 2.287161);
console.log(posMarker);
    // create the tile layer with correct attribution
    var osmUrl='http://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png';
    var osmAttrib='Map data © <a href="http://openstreetmap.org">OpenStreetMap</a> contributors';
    var osm = new L.TileLayer(osmUrl, {minZoom: 8, maxZoom: 18, attribution: osmAttrib});

    // start the map in South-East England
    map.setView(posMarker,9);
	map.setZoom(18);
	marker = L.marker([48.851658,2.28716]).addTo(map);
    map.addLayer(osm);
	console.log('yolo');
	setInterval(moveMarker, 100);
}

            var socket = io.connect('http://'+location.hostname+':8080');
            socket.on('message', function(message) {
		message = JSON.parse(message);
		console.log(message);
		 marker = new google.maps.Marker({
    			position: message,
    			map: map,
    			title: 'Hello World!'
  		});

            })
