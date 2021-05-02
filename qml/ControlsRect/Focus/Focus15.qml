import QtQuick 2.12
import QtQuick.Controls 2.12

FocusScope {
    id: focus15
    anchors.left: startButtonFocusScope.left
    anchors.top: focus13.bottom
    anchors.topMargin: 15
    height: 50
    anchors.right: startButtonFocusScope.horizontalCenter
    anchors.rightMargin: 15
    activeFocusOnTab: true
    Accessible.name: qsTr("First derivative control plus one")

    Keys.onSpacePressed: pressed()
    Keys.onEnterPressed: pressed()
    Keys.onReturnPressed: pressed()

    function pressed() {
        window.firstDerivative()
    }

    Rectangle {
        id: rect15
        anchors.fill: parent
        color: bgColor
        border.color: focus15.activeFocus ? lightColor : "light gray"
        border.width: focus15.activeFocus ? 2 : 1
        property bool checked: true
        property var text: "First derivative"

        signal clicked()

        Text {
            id: text
            text: rect15.text
            anchors.centerIn: parent
            font.pointSize: 10
            color: fontColor
        }

        MouseArea {
            anchors.fill: parent
            onClicked: focus15.pressed()
        }
    }

}
