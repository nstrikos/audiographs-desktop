import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

FocusScope {
    id: derivativeColorFocusScope
    height: 30
    width: 100
    anchors.verticalCenter: label10.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    property alias color: derivativeColorRect.color
    property alias derivativeColorRect: derivativeColorRect
    Accessible.name: qsTr("derivative color")
    activeFocusOnTab: true
    Keys.onSpacePressed: openColorDialog("derivative color")
    Keys.onEnterPressed: openColorDialog("derivative color")
    Keys.onReturnPressed: openColorDialog("derivative color")
    Rectangle {
        id: derivativeColorRect
        anchors.fill: parent
        color: derivativeColor
        border.color: derivativeColorFocusScope.activeFocus ? lightColor : "light gray"
        border.width: derivativeColorFocusScope.activeFocus ? 2 : 1
        MouseArea {
            anchors.fill: parent
            onPressed: {
                window.stopAudio()
                openColorDialog("derivative color")
            }
        }
    }
}
