
map = new google.maps.Map(
    document.getElementById("map"),
    {zoom: 15, center: start1}
    );
var arr = new Array(100);

for (var i = 0; i < arr.length; i++) {
    arr[i] = new Array(16);

}
function color_initialize() {
    var string = " ";




    for (var i = 0; i < arr.length; i++){
        string = "#"+(parseInt(Math.random()*0xffffff)).toString(16)
        arr[i] = string;
    }


}



function initialize(){


var string = ["red","blue","green","yellow","black","brown","pink","gray","orange","aqua"];

for(var i = 0; i < polyline.length; i++){

        marker[i] = new google.maps.Marker({
        position: polylinePath[i][0],
        map: map,
        icon : {
             path: google.maps.SymbolPath.CIRCLE,

             strokeColor: string[i],
             scale: 6
          }

    });
        polyline[i] = new google.maps.Polyline({
        path: polylinePath[i],
        strokeColor: string[i],
        strokeOpacity: 0.8,
        strokeWeight: 6,
        map: map
    });

}
}











 // 맵 생성
