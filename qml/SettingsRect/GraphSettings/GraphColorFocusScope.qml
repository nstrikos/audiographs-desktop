import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

FocusScope {
    id: graphColorFocusScope
    height: 30
    width: 100
    anchors.verticalCenter: label1.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    property alias color: lineColorRect.color
    activeFocusOnTab: true
    Accessible.name: qsTr("Graph color")
    Keys.onSpacePressed: openColorDialog("line color")
    Keys.onEnterPressed: openColorDialog("line color")
    Keys.onReturnPressed: openColorDialog("line color")
    
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
                openColorDialog("line color")
            }
        }
    }
}
