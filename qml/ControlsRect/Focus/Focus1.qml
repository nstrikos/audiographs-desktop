import QtQuick 2.12
import QtQuick.Controls 2.12

FocusScope {
    id: focus1
    anchors.left: startButtonFocusScope.left
    anchors.top: startButtonFocusScope.bottom
    anchors.topMargin: 15
    height: 50
    anchors.right: startButtonFocusScope.horizontalCenter
    anchors.rightMargin: 15
    activeFocusOnTab: true
    Accessible.name: qsTr("X")

    Keys.onSpacePressed: pressed()
    Keys.onEnterPressed: pressed()
    Keys.onReturnPressed: pressed()

    function pressed() {
        console.log("pressed")
        window.stopAudio()
        functionController.sayXCoordinate()
    }
    
    Rectangle {
        id: button1
        anchors.fill: parent
        color: bgColor
        border.color: focus1.activeFocus ? lightColor : "light gray"
        border.width: focus1.activeFocus ? 2 : 1
        property bool checked: true
        property var text: "X"
        
        signal clicked()
        
        Text {
            id: text
            text: button1.text
            anchors.centerIn: parent
            font.pointSize: 16
            color: fontColor
        }
        
        MouseArea {
            anchors.fill: parent
            onClicked: focus1.pressed()
        }
    }
}
