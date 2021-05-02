import QtQuick 2.12
import QtQuick.Controls 2.12

FocusScope {
    id: focus13
    anchors.left: startButtonFocusScope.left
    anchors.top: focus11.bottom
    anchors.topMargin: 15
    height: 50
    anchors.right: startButtonFocusScope.horizontalCenter
    anchors.rightMargin: 15
    activeFocusOnTab: true
    Accessible.name: qsTr("Derivative control plus d")

    Keys.onSpacePressed: pressed()
    Keys.onEnterPressed: pressed()
    Keys.onReturnPressed: pressed()

    function pressed() {
        window.sayDerivative()
    }

    Rectangle {
        id: rect13
        anchors.fill: parent
        color: bgColor
        border.color: focus13.activeFocus ? lightColor : "light gray"
        border.width: focus13.activeFocus ? 2 : 1
        property bool checked: true
        property var text: "Derivative"

        signal clicked()

        Text {
            id: text
            text: rect13.text
            anchors.centerIn: parent
            font.pointSize: 10
            color: fontColor
        }

        MouseArea {
            anchors.fill: parent
            onClicked: focus13.pressed()
        }
    }

}
