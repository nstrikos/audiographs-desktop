import QtQuick 2.12
import QtQuick.Controls 2.12

FocusScope {
    id: focus16
    anchors.left: startButtonFocusScope.horizontalCenter
    anchors.top: focus14.bottom
    anchors.topMargin: 15
    height: 50
    anchors.right: startButtonFocusScope.right
    anchors.leftMargin: 15
    activeFocusOnTab: true
    Accessible.name: qsTr("Second derivative control plus two")

    Keys.onSpacePressed: pressed()
    Keys.onEnterPressed: pressed()
    Keys.onReturnPressed: pressed()

    function pressed() {
        window.secondDerivative()
    }

    Rectangle {
        id: rect11
        anchors.fill: parent
        color: bgColor
        border.color: focus16.activeFocus ? lightColor : "light gray"
        border.width: focus16.activeFocus ? 2 : 1
        property bool checked: true
        property var text: "Second derivative"

        signal clicked()

        Text {
            id: text
            text: rect11.text
            anchors.centerIn: parent
            font.pointSize: 10
            color: fontColor
        }

        MouseArea {
            anchors.fill: parent
            onClicked: focus16.pressed()
        }
    }

}
