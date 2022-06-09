var webView = null;
var zIndex = 1;

var markerOverlays = new Array();
var my_markers = [];

var idMarker = 0;

//var pnt = new google.maps.LatLng(40.6246,22.9630);
//var newIcon = MapIconMaker.createMarkerIcon({width: 64, height: 64, primaryColor: "#00ff00"});

//gpsMarker.setLatLng(pnt);
//gpsMarker.LatLng = pnt;
//var gpsMarker = new google.maps.Marker({zIndexProcess:importanceOrder}, gpsIcon);
const myLatLng = { lat: -25.363, lng: 131.044 };
var map = null;


var gpsMarker = null;
var channel;
var infoWindow;

var pathCoordinates = [];
var pathPolyline;

function initialize() {
//  var point = new google.maps.LatLng(41.9246,22.9630);
  map = new google.maps.Map(document.getElementById("map"), {
        zoom: 14,
//        center: pnt,
      }
    );

  gpsMarker = new google.maps.Marker({
//      position: point,
      title: "Device position",
      map: map,
      draggable: true,
//      anchor: new google.maps.Point(16,48),
//      size: new google.maps.Size(32, 48),
//      size: new google.maps.Size(2, 4),
//      icon: 'https://www.dropbox.com/s/m3vfosmsi2llzey/gpsMarker.png?raw=1'
  });
  gpsMarker.importance = 5;

//  gpsMarker.setMap(map);
//  map.setCenter(point,2);

//  pathCoordinates.push(point);
  pathPolyline = new google.maps.Polyline({
      path: pathCoordinates,
      geodesic: true,
      strokeColor: "#FFA500",
      strokeOpacity: 1.0,
      strokeWeight: 2,
    });
    pathPolyline.setMap(map);
}

function MoveMe(x, y) {
  var newPoint = new google.maps.LatLng(x,y);
  //delayed so you can see it move

  setTimeout(function() {
    gpsMarker.setPosition(newPoint);
//    map.panTo(newPoint);
    pathCoordinates.push(newPoint);
    pathPolyline.setPath(pathCoordinates);
  }, 500);
}

function FindMe(x,y) {
    var point = new google.maps.LatLng(x,y);
    map.setCenter(point);
}

function InitZoom(x,y) {
    var point = new google.maps.LatLng(x, y);
    map.panTo(point)
    map.setCenter(point,12);
}

function DrawMarker(x, y, i, xy, h, adr, cmn, cat, num)
{
    var dataPoint = new google.maps.LatLng(x,y);

  var icon;
  switch (cat) {
    case 'Category: drill':
      icon = "https://www.dropbox.com/s/xpf0g8an8jfx5mf/drill.png?raw=1";
      break;
    case 'Category: well':
      icon = 'https://www.dropbox.com/s/05az1ufos1viao3/well.png?raw=1';
      break;
    case 'Category: spring':
      icon = "https://www.dropbox.com/s/71ncayud6m102hd/spring.png?raw=1";
      break;
  }


//    cIcon.shadow = 'https://dl.dropbox.com/u/80065506/images/shadow.png';
//    cIcon.iconSize = new GSize(32,32);
//    cIcon.shadowSize = new GSize(52,32);
//    cIcon.iconAnchor = new GPoint(16,32);
//    cIcon.infoWindowAnchor = new GPoint(16, 0);


    var dataMarker = new google.maps.Marker({
      zIndexProcess:importanceOrder,
      position: dataPoint,
      map: map,
      icon: icon
    });
    dataMarker.importance = 2;
//    dataMarker.setMap(map);


  infoWindow = new google.maps.InfoWindow({
      size: new google.maps.Size(150,50),
//      disableAutoPan : true
  });
  google.maps.event.addListener(dataMarker, 'click', function() {
     infoWindow.setContent('<p>ID: '       + i   + '</p>' +
                           '<p>Location: ' + xy  + '</p>' +
                           '<p>Altitude: ' + h   + '</p>' +
                           '<p>Adress: '   + adr + '</p>' +
                           '<p>Category: ' + cat + '</p>' +
                           '<p>Comments: ' + cmn + '</p>' +
                           '<button onclick="EditMarker('+ i +')">Edit</button>' +
                           '<button onclick="RemoveMarkerDB('+ i +')">Remove</button>'
                           );
     infoWindow.open(map, dataMarker);
     infoWindow.open(map);
  });

//    map.addOverlay(dataMarker);
    dataMarker.setMap(map)
    my_markers.push(dataMarker);
    return i;
}

function importanceOrder (marker,b) {
        return GOverlay.getZIndex(marker.getPoint().lat()) + marker.importance*1000000;
      }


function removeMarker(j) {
    my_markers[j].setMap(null);
}

function RemoveMarkerDB(j) {
  channel = new QWebChannel(qt.webChannelTransport, function (channel) {
    var JSobject = channel.objects.JSobject;
    JSobject.removeRowFromDB(j);
    infoWindow.close();
    removeMarker(j);
  });
}

function EditMarker(j) {
  channel = new QWebChannel(qt.webChannelTransport, function (channel) {
    // now you retrieve your object
    var JSobject = channel.objects.JSobject;
    JSobject.onEditClicked(j);
    infoWindow.close();
  });
}

function ClearMap() {
  var i;
  for (i = 0; i < my_markers.length; i++) {
    my_markers[i].setMap(null);
  }
  my_markers.length = 0;
//  gpsMarker.setMap(map)
}


