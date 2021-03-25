import QtQuick 2.12
import QtQuick.Controls 2.12

FocusScope {
    id: focus5
    anchors.left: startButtonFocusScope.left
    anchors.top: focus3.bottom
    anchors.topMargin: 15
    height: 50
    anchors.right: startButtonFocusScope.horizontalCenter
    anchors.rightMargin: 15
    activeFocusOnTab: true
    Accessible.name: qsTr("Previous point of interest")

    Keys.onSpacePressed: pressed()
    Keys.onEnterPressed: pressed()
    Keys.onReturnPressed: pressed()

    function pressed() {
        window.interestingPoint()
        functionController.previousPointInterest()
    }
    
    Rectangle {
        id: rect5
        anchors.fill: parent
        color: bgColor
        border.color: focus5.activeFocus ? lightColor : "light gray"
        border.width: focus5.activeFocus ? 2 : 1
        property bool checked: true
        property var text: "Previous point of interest"
        
        signal clicked()
        
        Text {
            id: text
            text: rect5.text
            anchors.centerIn: parent
            font.pointSize: 10
            color: fontColor
            wrapMode: Text.Wrap
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
        }
        
        MouseArea {
            anchors.fill: parent
            onClicked: focus5.pressed()
        }
    }
}
