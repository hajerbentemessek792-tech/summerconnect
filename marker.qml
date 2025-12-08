import QtQuick 6.7
import QtLocation 6.7
import QtPositioning 6.7

MapQuickItem {
    id: mk
    anchorPoint.x: 12
    anchorPoint.y: 12

    sourceItem: Rectangle {
        width: 24; height: 24
        radius: 12
        color: "red"
    }
}
