import QtQuick 2.15
import QtQuick.Controls 1.4
import QtQuick.Window 2.0
import QtLocation 5.6
import QtPositioning 5.6

Rectangle {
    id: mainWindow
    width: 512
    height: 512
    visible: true

    ListModel{
        id:dummyModel
        ListElement {
            Latitude: 47.212047
            Longitude: -1.551647
            Label: "something"
            Orientation: 0
            Color:"transparent"
        }
   }

    Plugin {
        id: googleMaps
        name: "googlemaps" // "mapboxgl", "esri", ...
        // specify plugin parameters if necessary
         PluginParameter {
            name:  "googlemaps.map.apikey";
            value:  "AIzaSyAvCSptRtTAUKyj9vcSslotxOSoqava4Lk"
         }

    }

    Map {
        id: myMap
        anchors.fill: parent
        plugin: googleMaps
        activeMapType: supportedMapTypes[1]

        center: QtPositioning.coordinate(59.91, 10.75) // Oslo
        zoomLevel: 14

        MapItemView{
            id:dynamicMapObject
            model: dummyModel
            delegate: MapQuickItem {
                coordinate: QtPositioning.coordinate(Latitude,Longitude)
                sourceItem:  Text{
                    width: 100
                    height: 50
                    text: model.Label
                    rotation: model.Orientation
                    opacity: 0.6
                    color: model.Color
                }
            }
        }

        MapPolyline {
                line.width: 3
                line.color: 'green'
                path: [
                    { latitude: 59.92, longitude: 10.77 },
                    { latitude: 59.96, longitude: 10.78 },
                    { latitude: 59.99, longitude: 10.76 },
                    { latitude: 59.95, longitude: 10.74 }
                ]
        }

        MapCircle {
          //a static item (fixed real dimension) always at 100m east of the map center
          id:prova
          center: myMap.center.atDistanceAndAzimuth(100,90)
          opacity:0.8
          color:"red"
          radius:30

        }
    }

    MouseArea {
           anchors.fill: parent
           acceptedButtons:  Qt.RightButton

           onClicked: {
                if (mouse.button === Qt.RightButton)
                {
                    dummyModel.append({
                        "Latitude": myMap.toCoordinate(Qt.point(mouseX,mouseY)).latitude ,"Longitude": myMap.toCoordinate(Qt.point(mouseX,mouseY)).longitude ,
                        "Label": "abc" , "Color": "red",
                        "Orientation":Number(3), })
                }
           }
    }

    Button{
        id:buttonMap
        text:"Click to add name"
        onClicked: {
            if(buttonMap.text == "Click to add name")
            {
                buttonMap.text = "Click to cancel name"
                myMap.activeMapType = myMap.supportedMapTypes[3]
            }
            else
            {
                buttonMap.text = "Click to add name"
                myMap.activeMapType = myMap.supportedMapTypes[1]
            }
        }
    }

    GroupBox{
           title:"map types"
           ComboBox{
               model:myMap.supportedMapTypes
               textRole:"description"
               onCurrentIndexChanged: myMap.activeMapType = myMap.supportedMapTypes[/*currentIndex*/0]
           }
     }
}
