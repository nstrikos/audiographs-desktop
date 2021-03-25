import QtQuick 2.12
import QtQuick.Controls 2.12

FocusScope {
    id: focus9
    anchors.left: startButtonFocusScope.left
    anchors.top: focus7.bottom
    anchors.topMargin: 15
    height: 50
    anchors.right: startButtonFocusScope.horizontalCenter
    anchors.rightMargin: 15
    
    activeFocusOnTab: true
    Accessible.name: qsTr("Previous point sound only")

    Keys.onSpacePressed: pressed()
    Keys.onEnterPressed: pressed()
    Keys.onReturnPressed: pressed()

    function pressed() {
        window.explore()
        functionController.previousPoint()
    }
    
    Rectangle {
        id: rect9
        anchors.fill: parent
        color: bgColor
        border.color: focus9.activeFocus ? lightColor : "light gray"
        border.width: focus9.activeFocus ? 2 : 1
        property bool checked: true
        property var text: "Previous point sound only"
        
        signal clicked()
        
        Text {
            id: text
            text: rect9.text
            anchors.centerIn: parent
            font.pointSize: 10
            color: fontColor
            wrapMode: Text.Wrap
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
        }
        
        MouseArea {
            anchors.fill: parent
            onClicked: focus9.pressed()
        }
    }
}
