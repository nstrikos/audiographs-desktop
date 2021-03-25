import QtQuick 2.12

Rectangle {
    width: parent.height
    height: 8
    rotation: 90
    anchors.left: parent.right
    transformOrigin: Item.TopLeft
    
    gradient: Gradient {
        GradientStop {
            color: Qt.rgba(0, 0, 0, 0.15)
            position: 0
        }
        GradientStop {
            color: Qt.rgba(0, 0, 0, 0.05)
            position: 0.5
        }
        GradientStop {
            color: Qt.rgba(0, 0, 0, 0)
            position: 1
        }
    }
}
