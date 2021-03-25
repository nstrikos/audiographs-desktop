import QtQuick 2.12
import QtQuick.Controls 2.12

FocusScope {
    id: focus11
    anchors.left: startButtonFocusScope.left
    anchors.top: focus9.bottom
    anchors.topMargin: 15
    height: 50
    anchors.right: startButtonFocusScope.horizontalCenter
    anchors.rightMargin: 15
    activeFocusOnTab: true
    Accessible.name: qsTr("Decrease step")

    Keys.onSpacePressed: pressed()
    Keys.onEnterPressed: pressed()
    Keys.onReturnPressed: pressed()

    function pressed() {
        functionController.decStep()
    }
    
    Rectangle {
        id: rect11
        anchors.fill: parent
        color: bgColor
        border.color: focus11.activeFocus ? lightColor : "light gray"
        border.width: focus11.activeFocus ? 2 : 1
        property bool checked: true
        property var text: "Decrease step"
        
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
            onClicked: focus11.pressed()
        }
    }
    
}
