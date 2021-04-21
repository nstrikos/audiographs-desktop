import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

FocusScope {
    id: highlightColorFocusScope
    height: 30
    width: 100
    anchors.verticalCenter: graphLabel4.verticalCenter
    //            anchors.left: label4.right
    //            anchors.leftMargin: 10
    anchors.right: parent.right
    anchors.rightMargin: 10
    property alias color: highlightColorRect.color
    activeFocusOnTab: true
    Accessible.name: qsTr("Highlight color")
    Keys.onSpacePressed: controlsMainRect.openColorDialog("highlight color")
    Keys.onEnterPressed: controlsMainRect.openColorDialog("highlight color")
    Keys.onReturnPressed: controlsMainRect.openColorDialog("hightlight color")
    
    Rectangle {
        id: highlightColorRect
        anchors.fill: parent
        color: highlightColor
        border.color: highlightColorFocusScope.activeFocus ? lightColor : "light gray"
        border.width: highlightColorFocusScope.activeFocus ? 2 : 1
        MouseArea {
            anchors.fill: parent
            onPressed: {
                window.stopAudio()
                controlsMainRect.openColorDialog("highlight color")
            }
        }
    }
}
