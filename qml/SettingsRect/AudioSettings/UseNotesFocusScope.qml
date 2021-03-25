import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

FocusScope {
    id: useNotesFocusScope
    height: 30
    width: 150
    anchors.verticalCenter: label4.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    property alias useNotesCheckBox: useNotesCheckBox
    property alias color: useNotesCheckBox.color
    activeFocusOnTab: true
    Accessible.name: qsTr("Use notes")
    
    Keys.onSpacePressed: useNotesCheckBox.checked = ! useNotesCheckBox.checked
    Keys.onEnterPressed: useNotesCheckBox.checked = ! useNotesCheckBox.checked
    Keys.onReturnPressed: useNotesCheckBox.checked = ! useNotesCheckBox.checked
    
    Rectangle {
        id: useNotesCheckBox
        anchors.fill: parent
        color: bgColor
        property bool checked: parameters.useNotes
        border.color: useNotesFocusScope.activeFocus ? lightColor : "light gray"
        border.width: useNotesFocusScope.activeFocus ? 2 : 1
        Text {
            text: useNotesCheckBox.checked ? qsTr("On") : qsTr("Off")
            anchors.centerIn: parent
            font.pointSize: 16
            color: fontColor
        }
        
        MouseArea {
            anchors.fill: parent
            onPressed: {
                useNotesCheckBox.checked = ! useNotesCheckBox.checked
            }
        }
        onCheckedChanged: {
            window.stopAudio()
            parameters.useNotes = checked
        }
    }
}
