import QtQuick 2.12
import QtQuick.Controls 2.12

FocusScope {
    id: focus6
    anchors.left: startButtonFocusScope.horizontalCenter
    anchors.leftMargin: 15
    anchors.top: focus4.bottom
    anchors.topMargin: 15
    anchors.right: startButtonFocusScope.right
    height: 50
    activeFocusOnTab: true
    Accessible.name: qsTr("Next point of interest")

    Keys.onSpacePressed: pressed()
    Keys.onEnterPressed: pressed()
    Keys.onReturnPressed: pressed()

    function pressed() {
        window.interestingPoint()
        functionController.nextPointInterest()
    }
    
    Rectangle {
        id: rect6
        anchors.fill: parent
        color: bgColor
        border.color: focus6.activeFocus ? lightColor : "light gray"
        border.width: focus6.activeFocus ? 2 : 1
        property bool checked: true
        property var text: "Next point of interest"
        
        signal clicked()
        
        Text {
            id: text
            text: rect6.text
            anchors.centerIn: parent
            font.pointSize: 10
            color: fontColor
            wrapMode: Text.Wrap
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
        }
        
        MouseArea {
            anchors.fill: parent
            onClicked: focus6.pressed()
        }
    }
}
