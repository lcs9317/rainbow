var map;
var polylinePath = [
    new google.maps.LatLng(37.4526437, 126.49236),
    new google.maps.LatLng(37.4768068, 126.4847975),
    new google.maps.LatLng(37.4988237, 126.4960839),
    new google.maps.LatLng(37.5176422, 126.5392841),
    new google.maps.LatLng(37.5398154, 126.5708743),
    new google.maps.LatLng(37.5457857, 126.5968815),
    new google.maps.LatLng(37.5646413, 126.6502792),
    new google.maps.LatLng(37.5708896, 126.7197823),
    new google.maps.LatLng(37.5710499, 126.7444216),
    new google.maps.LatLng(37.5770001, 126.7733532),
    new google.maps.LatLng(37.5817724, 126.799401),
    new google.maps.LatLng(37.5841817, 126.8167752),
    new google.maps.LatLng(37.5808037, 126.8313027),
    new google.maps.LatLng(37.5716637, 126.8473288),
    new google.maps.LatLng(37.56136, 126.8619116),
    new google.maps.LatLng(37.5487926, 126.8852035),
    new google.maps.LatLng(37.540747, 126.8910651),
    new google.maps.LatLng(37.5303713, 126.8925982),
    new google.maps.LatLng(37.5164746, 126.8825719),
    new google.maps.LatLng(37.5002697, 126.8725686),
    new google.maps.LatLng(37.4933399, 126.8711786),
    new google.maps.LatLng(37.4760577, 126.8756663),
    new google.maps.LatLng(37.4634352, 126.8887979),
    new google.maps.LatLng(37.448467, 126.8947082),
    new google.maps.LatLng(37.4346374, 126.8977132),
    new google.maps.LatLng(37.4242394, 126.8949032),
    new google.maps.LatLng(37.4033979, 126.8806084),
    new google.maps.LatLng(37.3848775, 126.8691937),
    new google.maps.LatLng(37.371033, 126.8693097),
    new google.maps.LatLng(37.3724101, 126.9126676),
    new google.maps.LatLng(37.3830471, 126.9660813),
    new google.maps.LatLng(37.3807849, 126.9762181),
    new google.maps.LatLng(37.3971504, 127.0267188),
    new google.maps.LatLng(37.3961676, 127.0715545),
    new google.maps.LatLng(37.3730718, 127.0659032),
    new google.maps.LatLng(37.35114, 127.063139),
    new google.maps.LatLng(37.3268898, 127.0575003),
    new google.maps.LatLng(37.3210994, 127.0517556),
    new google.maps.LatLng(37.3084352, 127.0590529),
    new google.maps.LatLng(37.2877049, 127.0692822),
    new google.maps.LatLng(37.2762087, 127.0808982)
];

function initialize(){


    var option = {lat: 37.4526437, lng: 126.49236};
    map = new google.maps.Map(
            document.getElementById("map"),
            {zoom: 8, center: option}
            );

    new google.maps.Marker(
        {position: option,
            map: map,
            label: "드론 시작 위치"}
    );

    var marker = new google.maps.Marker({
        position: polylinePath[polylinePath.length-1],
        map: map,
         label: "드론 마지막 위치"
    })

    var polyline = new google.maps.Polyline({
    path: polylinePath,
    strokeColor: '#FF0000',
    strokeOpacity: 0.8,
    strokeWeight: 6,
    map: map
});

}


initialize(); // 맵 생성
