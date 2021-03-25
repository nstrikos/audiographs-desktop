import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

Button {
    id: resetButton
    text: qsTr("Reset")
    anchors.top: label5.bottom
    anchors.topMargin: 30
    anchors.left: parent.left
    anchors.leftMargin: 10
    anchors.right: parent.right
    anchors.rightMargin: 10
    height: 50
    contentItem: Text {
        text: resetButton.text
        font: resetButton.font
        opacity: enabled ? 1.0 : 0.3
        color: fontColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }
    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 40
        opacity: enabled ? 1 : 0.3
        border.color: resetButton.activeFocus ? lightColor : "light gray"
        color: bgColor
        border.width: resetButton.activeFocus ? 2 : 1
        radius: 2
    }
    Accessible.name: qsTr("Reset audio settings")
    onClicked: {
        parameters.resetAudio()
        durationSpinbox.value = parameters.duration
        minFreqSpinbox.value = parameters.minFreq
        maxFreqSpinbox.value = parameters.maxFreq
        useNotesFocusScope.useNotesCheckBox.checked = parameters.useNotes
        window.stopAudio()
    }
}
