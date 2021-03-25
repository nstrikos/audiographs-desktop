import QtQuick 2.12
import QtQuick.Controls 2.12

FocusScope {
    id: focus7
    anchors.left: startButtonFocusScope.left
    anchors.top: focus5.bottom
    anchors.topMargin: 15
    height: 50
    anchors.right: startButtonFocusScope.horizontalCenter
    anchors.rightMargin: 15
    activeFocusOnTab: true
    Accessible.name: qsTr("Previous point of interest fast mode")

    Keys.onSpacePressed: pressed()
    Keys.onEnterPressed: pressed()
    Keys.onReturnPressed: pressed()

    function pressed() {
        window.interestingPoint()
        functionController.previousPointInterestFast()
    }
    
    Rectangle {
        id: rect7
        anchors.fill: parent
        color: bgColor
        border.color: focus7.activeFocus ? lightColor : "light gray"
        border.width: focus7.activeFocus ? 2 : 1
        property bool checked: true
        property var text: "Previous point of interest fast mode"
        
        signal clicked()
        
        Text {
            id: text
            text: rect7.text
            anchors.centerIn: parent
            font.pointSize: 10
            color: fontColor
            wrapMode: Text.Wrap
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
        }
        
        MouseArea {
            anchors.fill: parent
            onClicked: focus7.pressed()
        }
    }
}
