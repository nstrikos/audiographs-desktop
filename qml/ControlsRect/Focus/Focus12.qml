import QtQuick 2.12
import QtQuick.Controls 2.12

FocusScope {
    id: focus12
    anchors.left: startButtonFocusScope.horizontalCenter
    anchors.leftMargin: 15
    anchors.top: focus10.bottom
    anchors.topMargin: 15
    anchors.right: startButtonFocusScope.right
    height: 50
    
    activeFocusOnTab: true
    Accessible.name: qsTr("Increase step")

    Keys.onSpacePressed: pressed()
    Keys.onEnterPressed: pressed()
    Keys.onReturnPressed: pressed()

    function pressed() {
        functionController.incStep()
    }
    
    Rectangle {
        id: rect12
        anchors.fill: parent
        color: bgColor
        border.color: focus12.activeFocus ? lightColor : "light gray"
        border.width: focus12.activeFocus ? 2 : 1
        property bool checked: true
        property var text: "Increase step"
        
        signal clicked()
        
        Text {
            id: text
            text: rect12.text
            anchors.centerIn: parent
            font.pointSize: 10
            color: fontColor
        }
        
        MouseArea {
            anchors.fill: parent
            onClicked: focus12.pressed()
        }
    }
}
