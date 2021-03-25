import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

FocusScope {
    id: exploreModeFocusScope
    height: 30
    width: 150
    anchors.verticalCenter: label5.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    property alias color: exploreModeCheckBox.color
    activeFocusOnTab: true
    Accessible.name: qsTr("Explore mode")
    
    Keys.onSpacePressed: exploreModeCheckBox.checked = ! exploreModeCheckBox.checked
    Keys.onEnterPressed: exploreModeCheckBox.checked = ! exploreModeCheckBox.checked
    Keys.onReturnPressed: exploreModeCheckBox.checked = ! exploreModeCheckBox.checked
    
    Rectangle {
        id: exploreModeCheckBox
        anchors.fill: parent
        color: bgColor
        property bool checked: parameters.exploreMode
        border.color: exploreModeFocusScope.activeFocus ? lightColor : "light gray"
        border.width: exploreModeFocusScope.activeFocus ? 2 : 1
        Text {
            text: exploreModeCheckBox.checked ? qsTr("On") : qsTr("Off")
            anchors.centerIn: parent
            font.pointSize: 16
            color: fontColor
        }
        
        MouseArea {
            anchors.fill: parent
            onPressed: {
                exploreModeCheckBox.checked = ! exploreModeCheckBox.checked
            }
        }
        onCheckedChanged: {
            window.stopAudio()
            parameters.exploreMode = checked
        }
    }
}
