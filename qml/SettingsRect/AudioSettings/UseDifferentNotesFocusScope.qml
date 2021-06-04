import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

FocusScope {
    id: useDifferentNotesFocusScope
    height: 30
    width: 150
    anchors.verticalCenter: audioLabel6.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    property alias useDifferentNotesCheckBox: useDifferentNotesCheckBox
    property alias color: useDifferentNotesCheckBox.color
    activeFocusOnTab: true
    Accessible.name: qsTr("Use different notes for negative values control plus f four")

    Keys.onSpacePressed: useDifferentNotesCheckBox.checked = !useDifferentNotesCheckBox.checked
    Keys.onEnterPressed: useDifferentNotesCheckBox.checked = !useDifferentNotesCheckBox.checked
    Keys.onReturnPressed: useDifferentNotesCheckBox.checked = !useDifferentNotesCheckBox.checked

    Rectangle {
        id: useDifferentNotesCheckBox
        anchors.fill: parent
        color: bgColor
        property bool checked: parameters.useNegativeNotes
        border.color: useDifferentNotesFocusScope.activeFocus ? lightColor : "light gray"
        border.width: useDifferentNotesFocusScope.activeFocus ? 2 : 1
        Text {
            text: useDifferentNotesCheckBox.checked ? qsTr("On") : qsTr("Off")
            anchors.centerIn: parent
            font.pointSize: 16
            color: fontColor
        }

        MouseArea {
            anchors.fill: parent
            onPressed: {
                useDifferentNotesCheckBox.checked = !useDifferentNotesCheckBox.checked
            }
        }
        onCheckedChanged: {
            window.stopAudio()
            parameters.useNegativeNotes = checked
            textToSpeech.speak(useDifferentNotesFocusScope.Accessible.name + " " + parameters.useNegativeNotes)
        }
    }
}
