import QtQuick 2.12
import QtQuick.Controls 2.12

FocusScope {
    id: focus4
    anchors.left: startButtonFocusScope.horizontalCenter
    anchors.leftMargin: 15
    anchors.top: focus2.bottom
    anchors.topMargin: 15
    anchors.right: startButtonFocusScope.right
    height: 50
    activeFocusOnTab: true
    Accessible.name: qsTr("Next point")

    Keys.onSpacePressed: pressed()
    Keys.onEnterPressed: pressed()
    Keys.onReturnPressed: pressed()

    function pressed() {
        window.explore()
        functionController.nextPointY();
    }
    
    Rectangle {
        id: rect4
        anchors.fill: parent
        color: bgColor
        border.color: focus4.activeFocus ? lightColor : "light gray"
        border.width: focus4.activeFocus ? 2 : 1
        property bool checked: true
        property var text: "Next point"
        
        signal clicked()
        
        Text {
            id: text
            text: rect4.text
            anchors.centerIn: parent
            font.pointSize: 10
            color: fontColor
        }
        
        MouseArea {
            anchors.fill: parent
            onClicked: focus4.pressed()
        }
    }
}
