import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

SpinBox {
    id: precisionSpinbox
    height: 30
    width: 150
    anchors.verticalCenter: label33.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    activeFocusOnTab: true
    Accessible.name: qsTr("Precision digits")
    value: parameters.precisionDigits
    from: 0
    to: 5
    onValueChanged: {
        window.stopAudio()
        parameters.precisionDigits = value
    }
    
    editable: false
    
    contentItem: TextInput {
        z: 2
        text: precisionSpinbox.textFromValue(precisionSpinbox.value, precisionSpinbox.locale)
        
        font: precisionSpinbox.font
        color: fontColor
        selectionColor: "#21be2b"
        selectedTextColor: "#ffffff"
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        
        readOnly: !precisionSpinbox.editable
        validator: precisionSpinbox.validator
        inputMethodHints: Qt.ImhFormattedNumbersOnly
    }
    
    up.indicator: Rectangle {
        x: precisionSpinbox.mirrored ? 0 : parent.width - width
        height: parent.height
        implicitWidth: 30
        implicitHeight: 30
        color: "light gray"
        border.color: {
            if (precisionSpinbox.activeFocus) {
                if (invertTheme)
                    return "yellow"
                else
                    return "blue"
            }
            else {
                return "light gray"
            }
        }
        border.width: precisionSpinbox.activeFocus ? 2 : 1
        
        Text {
            text: "+"
            font.pixelSize: precisionSpinbox.font.pixelSize * 2
            color: fontColor
            anchors.fill: parent
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
    
    down.indicator: Rectangle {
        x: precisionSpinbox.mirrored ? parent.width - width : 0
        height: parent.height
        implicitWidth: 30
        implicitHeight: 30
        color: "light gray"
        border.color: {
            if (precisionSpinbox.activeFocus) {
                if (invertTheme)
                    return "yellow"
                else
                    return "blue"
            }
            else {
                return "light gray"
            }
        }
        border.width: precisionSpinbox.activeFocus ? 2 : 1
        
        Text {
            text: "-"
            font.pixelSize: precisionSpinbox.font.pixelSize * 2
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
            if (precisionSpinbox.activeFocus) {
                if (invertTheme)
                    return "yellow"
                else
                    return "blue"
            }
            else {
                return "light gray"
            }
        }
        border.width: precisionSpinbox.activeFocus ? 2 : 1
    }
}
