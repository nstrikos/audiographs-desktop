import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

SpinBox {
    id: highlightSizeSpinbox
    height: 30
    width: 100
    anchors.verticalCenter: label5.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    from: 5
    to: 20
    value: parameters.highlightSize
    Accessible.name: qsTr("Highlight size")
    onValueChanged: {
        window.stopAudio()
        graphRect.highlightSize = value
        parameters.highlightSize = value
    }
    editable: false
    
    contentItem: TextInput {
        z: 2
        text: highlightSizeSpinbox.textFromValue(highlightSizeSpinbox.value, highlightSizeSpinbox.locale)
        
        font: highlightSizeSpinbox.font
        color: fontColor
        selectionColor: "#21be2b"
        selectedTextColor: "#ffffff"
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        
        readOnly: !highlightSizeSpinbox.editable
        validator: highlightSizeSpinbox.validator
        inputMethodHints: Qt.ImhFormattedNumbersOnly
    }
    
    up.indicator: Rectangle {
        x: highlightSizeSpinbox.mirrored ? 0 : parent.width - width
        height: parent.height
        implicitWidth: 30
        implicitHeight: 30
        color: "light gray"
        border.color: {
            if (highlightSizeSpinbox.activeFocus) {
                if (invertTheme)
                    return "yellow"
                else
                    return "blue"
            }
            else {
                return "light gray"
            }
        }
        border.width: highlightSizeSpinbox.activeFocus ? 2 : 1
        
        Text {
            text: "+"
            font.pixelSize: highlightSizeSpinbox.font.pixelSize * 2
            color: fontColor
            anchors.fill: parent
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
    
    down.indicator: Rectangle {
        x: highlightSizeSpinbox.mirrored ? parent.width - width : 0
        height: parent.height
        implicitWidth: 30
        implicitHeight: 30
        color: "light gray"
        border.color: {
            if (highlightSizeSpinbox.activeFocus) {
                if (invertTheme)
                    return "yellow"
                else
                    return "blue"
            }
            else {
                return "light gray"
            }
        }
        border.width: highlightSizeSpinbox.activeFocus ? 2 : 1
        
        Text {
            text: "-"
            font.pixelSize: highlightSizeSpinbox.font.pixelSize * 2
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
            if (highlightSizeSpinbox.activeFocus) {
                if (invertTheme)
                    return "yellow"
                else
                    return "blue"
            }
            else {
                return "light gray"
            }
        }
        border.width: highlightSizeSpinbox.activeFocus ? 2 : 1
    }
}
