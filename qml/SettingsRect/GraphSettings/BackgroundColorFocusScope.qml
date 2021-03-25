import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

FocusScope {
    id: backgroundColorFocusScope
    height: 30
    width: 100
    anchors.verticalCenter: label2.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    activeFocusOnTab: true
    property alias color: backGroundColorRect.color
    Accessible.name: qsTr("Background color")
    Keys.onSpacePressed: openColorDialog("background color")
    Keys.onEnterPressed: openColorDialog("background color")
    Keys.onReturnPressed: openColorDialog("background color")
    Rectangle {
        id: backGroundColorRect
        anchors.fill: parent
        color: backgroundColor
        border.color: backgroundColorFocusScope.activeFocus ? lightColor : "light gray"
        border.width: backgroundColorFocusScope.activeFocus ? 2 : 1
        MouseArea {
            anchors.fill: parent
            onPressed: {
                window.stopAudio()
                openColorDialog("background color")
            }
        }
    }
}
