import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

FocusScope {
    id: graphColorFocusScope
    height: 30
    width: 100
    anchors.verticalCenter: graphLabel1.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    property alias color: lineColorRect.color
    activeFocusOnTab: true
    Accessible.name: qsTr("Graph color")
    Keys.onSpacePressed: controlsMainRect.openColorDialog("line color")
    Keys.onEnterPressed: controlsMainRect.openColorDialog("line color")
    Keys.onReturnPressed: controlsMainRect.openColorDialog("line color")
    
    Rectangle {
        id: lineColorRect
        anchors.fill: parent
        color: lineColor
        border.color: graphColorFocusScope.activeFocus ? lightColor : "light gray"
        border.width: graphColorFocusScope.activeFocus ? 2 : 1
        MouseArea {
            anchors.fill: parent
            onPressed: {
                window.stopAudio()
                controlsMainRect.openColorDialog("line color")
            }
        }
    }
}
