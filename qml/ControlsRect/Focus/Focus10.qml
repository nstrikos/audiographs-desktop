import QtQuick 2.12
import QtQuick.Controls 2.12

FocusScope {
    id: focus10
    anchors.left: startButtonFocusScope.horizontalCenter
    anchors.leftMargin: 15
    anchors.top: focus8.bottom
    anchors.topMargin: 15
    anchors.right: startButtonFocusScope.right
    height: 50
    
    activeFocusOnTab: true
    Accessible.name: qsTr("Next point sound only")

    Keys.onSpacePressed: pressed()
    Keys.onEnterPressed: pressed()
    Keys.onReturnPressed: pressed()

    function pressed() {
        window.explore()
        functionController.nextPoint()
    }
    
    Rectangle {
        id: rect10
        anchors.fill: parent
        color: bgColor
        border.color: focus10.activeFocus ? lightColor : "light gray"
        border.width: focus10.activeFocus ? 2 : 1
        property bool checked: true
        property var text: "Next point sound only"
        
        signal clicked()
        
        Text {
            id: text
            text: rect10.text
            anchors.centerIn: parent
            font.pointSize: 10
            color: fontColor
            wrapMode: Text.Wrap
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
        }
        
        MouseArea {
            anchors.fill: parent
            onClicked: focus10.pressed()
        }
    }
}
