

    map = new google.maps.Map(
            document.getElementById("map"),
            {zoom: 8, center: start1}
            );



    //드론 마커
    var D_image1 = 'drone1.png';
    var D_image2 = 'drone2.png';
    new google.maps.Marker(
        {position: start1,
            map: map,
            icon:D_image1
         }
    );

    new google.maps.Marker(
        {position: start2,
            map: map,
            icon:D_image2}
    );

    var marker = new google.maps.Marker({
        position: polylinePath[0][polylinePath.length-1],
        map: map,
         icon:D_image1
    });

    var marker2 = new google.maps.Marker({
        position: polylinePath[1][polylinePath.length-1],
        map: map,
        icon:D_image2
    });



    polyline[0] = new google.maps.Polyline({
    path: polylinePath[0],
    strokeColor: "red",
    strokeOpacity: 0.8,
    strokeWeight: 6,
    map: map
});

    polyline[1] = new google.maps.Polyline({
    path: polylinePath[1],
    strokeColor: "blue",
    strokeOpacity: 0.8,
    strokeWeight: 6,
    map: map
 });
    polyline[2] = new google.maps.Polyline({
    path: polylinePath[2],
    strokeColor: "green",
    strokeOpacity: 0.8,
    strokeWeight: 6,
    map: map
    });
    polyline[3] = new google.maps.Polyline({
    path: polylinePath[3],
    strokeColor: "black",
    strokeOpacity: 0.8,
    strokeWeight: 6,
    map: map
    });

}



 // 맵 생성
