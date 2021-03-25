import QtQuick 2.12
import QtQuick.Controls 2.12

FocusScope {
    id: focus3
    anchors.left: startButtonFocusScope.left
    anchors.top: focus1.bottom
    anchors.topMargin: 15
    height: 50
    anchors.right: startButtonFocusScope.horizontalCenter
    anchors.rightMargin: 15
    activeFocusOnTab: true
    Accessible.name: qsTr("Previous point")

    Keys.onSpacePressed: pressed()
    Keys.onEnterPressed: pressed()
    Keys.onReturnPressed: pressed()

    function pressed() {
        window.explore()
        functionController.previousPointY();
    }
    
    Rectangle {
        id: rect3
        anchors.fill: parent
        color: bgColor
        border.color: focus3.activeFocus ? lightColor : "light gray"
        border.width: focus3.activeFocus ? 2 : 1
        property bool checked: true
        property var text: "Previous point"
        
        signal clicked()
        
        Text {
            id: text
            text: rect3.text
            anchors.centerIn: parent
            font.pointSize: 10
            color: fontColor
        }
        
        MouseArea {
            anchors.fill: parent
            onClicked: focus3.pressed()
        }
    }
    
}
