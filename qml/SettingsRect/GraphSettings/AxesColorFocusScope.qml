import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

FocusScope {
    id: axesColorFocusScope
    height: 30
    width: 100
    anchors.verticalCenter: label6.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    property alias color: axesColorRect.color
    property alias axesColorRect: axesColorRect
    Accessible.name: qsTr("Axes color")
    activeFocusOnTab: true
    Keys.onSpacePressed: openColorDialog("axes color")
    Keys.onEnterPressed: openColorDialog("axes color")
    Keys.onReturnPressed: openColorDialog("axes color")
    Rectangle {
        id: axesColorRect
        anchors.fill: parent
        color: axesColor
        border.color: axesColorFocusScope.activeFocus ? lightColor : "light gray"
        border.width: axesColorFocusScope.activeFocus ? 2 : 1
        MouseArea {
            anchors.fill: parent
            onPressed: {
                window.stopAudio()
                openColorDialog("axes color")
            }
        }
    }
}
