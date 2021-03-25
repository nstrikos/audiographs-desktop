import QtQuick 2.12
import QtQuick.Controls 2.12

FocusScope {
    id: focus2
    anchors.left: startButtonFocusScope.horizontalCenter
    anchors.leftMargin: 15
    anchors.top: startButtonFocusScope.bottom
    anchors.topMargin: 15
    height: 50
    anchors.right: startButtonFocusScope.right
    activeFocusOnTab: true
    Accessible.name: qsTr("Y")

    Keys.onSpacePressed: pressed()
    Keys.onEnterPressed: pressed()
    Keys.onReturnPressed: pressed()

    function pressed() {
        window.stopAudio()
        functionController.sayYCoordinate()
    }
    
    Rectangle {
        id: button2
        anchors.fill: parent
        color: bgColor
        border.color: focus2.activeFocus ? lightColor : "light gray"
        border.width: focus2.activeFocus ? 2 : 1
        property bool checked: true
        property var text: "Y"
        
        signal clicked()
        
        Text {
            id: text2
            text: button2.text
            anchors.centerIn: parent
            font.pointSize: 16
            color: fontColor
        }
        
        MouseArea {
            anchors.fill: parent
            onClicked: focus2.pressed()
        }
    }
}
