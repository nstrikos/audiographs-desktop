import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

SpinBox {
    id: minFreqSpinbox
    height: 30
    width: 150
    anchors.verticalCenter: label2.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    activeFocusOnTab: true
    Accessible.name: qsTr("Minimum frequency")
    value: parameters.minFreq
    from: 200
    to: 4000
    stepSize: 100
    onValueChanged: {
        window.stopAudio()
        parameters.minFreq = value
    }
    
    editable: false
    
    contentItem: TextInput {
        z: 2
        text: minFreqSpinbox.textFromValue(minFreqSpinbox.value, minFreqSpinbox.locale)
        
        font: minFreqSpinbox.font
        color: fontColor
        selectionColor: "#21be2b"
        selectedTextColor: "#ffffff"
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        
        readOnly: !minFreqSpinbox.editable
        validator: minFreqSpinbox.validator
        inputMethodHints: Qt.ImhFormattedNumbersOnly
    }
    
    up.indicator: Rectangle {
        x: minFreqSpinbox.mirrored ? 0 : parent.width - width
        height: parent.height
        implicitWidth: 30
        implicitHeight: 30
        color: "light gray"
        border.color: {
            if (minFreqSpinbox.activeFocus) {
                if (invertTheme)
                    return "yellow"
                else
                    return "blue"
            }
            else {
                return "light gray"
            }
        }
        border.width: minFreqSpinbox.activeFocus ? 2 : 1
        Text {
            text: "+"
            font.pixelSize: minFreqSpinbox.font.pixelSize * 2
            color: fontColor
            anchors.fill: parent
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
    
    down.indicator: Rectangle {
        x: minFreqSpinbox.mirrored ? parent.width - width : 0
        height: parent.height
        implicitWidth: 30
        implicitHeight: 30
        color: "light gray"
        border.color: {
            if (minFreqSpinbox.activeFocus) {
                if (invertTheme)
                    return "yellow"
                else
                    return "blue"
            }
            else {
                return "light gray"
            }
        }
        border.width: minFreqSpinbox.activeFocus ? 2 : 1
        
        
        Text {
            text: "-"
            font.pixelSize: minFreqSpinbox.font.pixelSize * 2
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
            if (minFreqSpinbox.activeFocus) {
                if (invertTheme)
                    return "yellow"
                else
                    return "blue"
            }
            else {
                return "light gray"
            }
        }
        border.width: minFreqSpinbox.activeFocus ? 2 : 1
    }
}
