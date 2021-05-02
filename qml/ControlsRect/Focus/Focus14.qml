import QtQuick 2.12
import QtQuick.Controls 2.12

FocusScope {
    id: focus14
    anchors.left: startButtonFocusScope.horizontalCenter
    anchors.top: focus12.bottom
    anchors.topMargin: 15
    height: 50
    anchors.right: startButtonFocusScope.right
    anchors.leftMargin: 15
    activeFocusOnTab: true
    Accessible.name: qsTr("Normal mode control plus 0")

    Keys.onSpacePressed: pressed()
    Keys.onEnterPressed: pressed()
    Keys.onReturnPressed: pressed()

    function pressed() {
        window.normalDerivative()
    }

    Rectangle {
        id: rect14
        anchors.fill: parent
        color: bgColor
        border.color: focus14.activeFocus ? lightColor : "light gray"
        border.width: focus14.activeFocus ? 2 : 1
        property bool checked: true
        property var text: "Normal mode"

        signal clicked()

        Text {
            id: text
            text: rect14.text
            anchors.centerIn: parent
            font.pointSize: 10
            color: fontColor
        }

        MouseArea {
            anchors.fill: parent
            onClicked: focus14.pressed()
        }
    }

}
