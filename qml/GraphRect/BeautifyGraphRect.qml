import QtQuick 2.0

Rectangle {
    width: parent.width
    height: 8
    anchors.left: parent.left
    anchors.bottom: parent.bottom
    z: 1010101
    visible: (controlsRect.height > 0) && (!anchorToLeft)
    gradient: Gradient {
        GradientStop {
            color: Qt.rgba(0, 0, 0, 0.4)
            position: 1
        }
        GradientStop {
            color: Qt.rgba(0, 0, 0, 0.15)
            position: 0.5
        }
        GradientStop {
            color: Qt.rgba(0, 0, 0, 0)
            position: 0
        }
    }
}
