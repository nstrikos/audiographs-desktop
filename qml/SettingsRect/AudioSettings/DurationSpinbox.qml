import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

SpinBox {
    id: durationSpinbox
    height: 30
    width: 150
    anchors.verticalCenter: audioLabel1.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
//    activeFocusOnTab: true
    Accessible.name: qsTr("Duration")
    value: parameters.duration
    from: 10
    to: 100
    onValueChanged: {
        window.stopAudio()
        parameters.duration = value
    }
    
    editable: false
    
    contentItem: TextInput {
        z: 2
        text: durationSpinbox.textFromValue(durationSpinbox.value, durationSpinbox.locale)
        
        font: durationSpinbox.font
        color: fontColor
        selectionColor: "#21be2b"
        selectedTextColor: "#ffffff"
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        
        readOnly: !durationSpinbox.editable
        validator: durationSpinbox.validator
        inputMethodHints: Qt.ImhFormattedNumbersOnly
    }
    
    up.indicator: Rectangle {
        x: durationSpinbox.mirrored ? 0 : parent.width - width
        height: parent.height
        implicitWidth: 30
        implicitHeight: 30
        color: "light gray"
        border.color: {
            if (durationSpinbox.activeFocus) {
                if (invertTheme)
                    return "yellow"
                else
                    return "blue"
            }
            else {
                return "light gray"
            }
        }
        border.width: durationSpinbox.activeFocus ? 2 : 1
        
        Text {
            text: "+"
            font.pixelSize: durationSpinbox.font.pixelSize * 2
            color: fontColor
            anchors.fill: parent
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
    
    down.indicator: Rectangle {
        x: durationSpinbox.mirrored ? parent.width - width : 0
        height: parent.height
        implicitWidth: 30
        implicitHeight: 30
        color: "light gray"
        border.color: {
            if (durationSpinbox.activeFocus) {
                if (invertTheme)
                    return "yellow"
                else
                    return "blue"
            }
            else {
                return "light gray"
            }
        }
        border.width: durationSpinbox.activeFocus ? 2 : 1
        
        Text {
            text: "-"
            font.pixelSize: durationSpinbox.font.pixelSize * 2
            color: fontColor
            anchors.fill: parent
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
    
    background: Rectangle {
        implicitWidth: 140
        color: bgColor
        border.color: {
            if (durationSpinbox.activeFocus) {
                if (invertTheme)
                    return "yellow"
                else
                    return "blue"
            }
            else {
                return "light gray"
            }
        }
        border.width: durationSpinbox.activeFocus ? 2 : 1
    }
    
}
