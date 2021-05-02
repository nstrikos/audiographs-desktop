import QtQuick 2.12
import QtQuick.Controls 2.12

FocusScope {
    id: focus8
    anchors.left: startButtonFocusScope.horizontalCenter
    anchors.leftMargin: 15
    anchors.top: focus6.bottom
    anchors.topMargin: 15
    anchors.right: startButtonFocusScope.right
    height: 50
    activeFocusOnTab: true
    Accessible.name: qsTr("Next point fast shift plus right")

    Keys.onSpacePressed: pressed()
    Keys.onEnterPressed: pressed()
    Keys.onReturnPressed: pressed()

    function pressed() {
        window.nextFast()
    }
    
    Rectangle {
        id: rect8
        anchors.fill: parent
        color: bgColor
        border.color: focus8.activeFocus ? lightColor : "light gray"
        border.width: focus8.activeFocus ? 2 : 1
        property bool checked: true
        property var text: "Next point (fast)"
        
        signal clicked()
        
        Text {
            id: text
            text: rect8.text
            anchors.centerIn: parent
            font.pointSize: 10
            color: fontColor
            wrapMode: Text.Wrap
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
        }
        
        MouseArea {
            anchors.fill: parent
            onClicked: focus8.pressed()
        }
    }
}
