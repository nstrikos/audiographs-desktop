import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

SpinBox {
    id: maxFreqSpinbox
    height: 30
    width: 150
    anchors.verticalCenter: label3.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    activeFocusOnTab: true
    Accessible.name: qsTr("Maximum frequency")
    value: parameters.maxFreq
    from: 400
    to: 8000
    stepSize: 100
    onValueChanged: {
        window.stopAudio()
        parameters.maxFreq = value
    }
    
    editable: false
    
    contentItem: TextInput {
        z: 2
        text: maxFreqSpinbox.textFromValue(maxFreqSpinbox.value, maxFreqSpinbox.locale)
        
        font: maxFreqSpinbox.font
        color: fontColor
        selectionColor: "#21be2b"
        selectedTextColor: "#ffffff"
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        
        readOnly: !maxFreqSpinbox.editable
        validator: maxFreqSpinbox.validator
        inputMethodHints: Qt.ImhFormattedNumbersOnly
    }
    
    up.indicator: Rectangle {
        x: maxFreqSpinbox.mirrored ? 0 : parent.width - width
        height: parent.height
        implicitWidth: 30
        implicitHeight: 30
        color: "light gray"
        border.color: {
            if (maxFreqSpinbox.activeFocus) {
                if (invertTheme)
                    return "yellow"
                else
                    return "blue"
            }
            else {
                return "light gray"
            }
        }
        border.width: maxFreqSpinbox.activeFocus ? 2 : 1
        
        Text {
            text: "+"
            font.pixelSize: maxFreqSpinbox.font.pixelSize * 2
            color: fontColor
            anchors.fill: parent
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
    
    down.indicator: Rectangle {
        x: maxFreqSpinbox.mirrored ? parent.width - width : 0
        height: parent.height
        implicitWidth: 30
        implicitHeight: 30
        color: "light gray"
        border.color: {
            if (maxFreqSpinbox.activeFocus) {
                if (invertTheme)
                    return "yellow"
                else
                    return "blue"
            }
            else {
                return "light gray"
            }
        }
        
        border.width: maxFreqSpinbox.activeFocus ? 2 : 1
        
        
        Text {
            text: "-"
            font.pixelSize: maxFreqSpinbox.font.pixelSize * 2
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
            if (maxFreqSpinbox.activeFocus) {
                if (invertTheme)
                    return "yellow"
                else
                    return "blue"
            }
            else {
                return "light gray"
            }
        }
        border.width: maxFreqSpinbox.activeFocus ? 2 : 1
    }
}
