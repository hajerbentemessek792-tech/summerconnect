import QtQuick 2.15
import QtLocation 6.7
import QtPositioning 6.7

Map {
    id: map
    anchors.fill: parent
    plugin: Plugin { name: "osm" }

    function setCenter(lat, lon) {
        map.center = QtPositioning.coordinate(lat, lon)
    }

    function addMarker(lat, lon) {
        map.addMapItem(MapQuickItem {
            coordinate: QtPositioning.coordinate(lat, lon)
            anchorPoint.x: 12
            anchorPoint.y: 12
            sourceItem: Rectangle {
                width: 24
                height: 24
                color: "red"
                radius: 12
            }
        })
    }

    Component.onCompleted: {
        map.center = QtPositioning.coordinate(36.8, 10.2) // centre par défaut
        map.zoomLevel = 12
    }
}
