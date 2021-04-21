import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

FocusScope {
    id: axesColorFocusScope
    height: 30
    width: 100
    anchors.verticalCenter: graphLabel6.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    property alias color: axesColorRect.color
    property alias axesColorRect: axesColorRect
    Accessible.name: qsTr("Axes color")
    activeFocusOnTab: true
    Keys.onSpacePressed: controlsMainRect.openColorDialog("axes color")
    Keys.onEnterPressed: controlsMainRect.openColorDialog("axes color")
    Keys.onReturnPressed: controlsMainRect.                                         openColorDialog("axes color")
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
                controlsMainRect.openColorDialog("axes color")
            }
        }
    }
}
