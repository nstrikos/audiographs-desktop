import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

SpinBox {
    id: axesSizeSpinbox
    height: 30
    width: 100
    anchors.verticalCenter: label7.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    from: 1
    to: 10
    value: parameters.axesSize
    Accessible.name: qsTr("Axes size")
    onValueChanged: {
        window.stopAudio()
        parameters.axesSize = value
        graphRect.graphCanvas.updateCanvas()
    }
    editable: false
    
    contentItem: TextInput {
        z: 2
        text: axesSizeSpinbox.textFromValue(axesSizeSpinbox.value, axesSizeSpinbox.locale)
        
        font: axesSizeSpinbox.font
        color: fontColor
        selectionColor: "#21be2b"
        selectedTextColor: "#ffffff"
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        
        readOnly: !axesSizeSpinbox.editable
        validator: axesSizeSpinbox.validator
        inputMethodHints: Qt.ImhFormattedNumbersOnly
    }
    
    up.indicator: Rectangle {
        x: axesSizeSpinbox.mirrored ? 0 : parent.width - width
        height: parent.height
        implicitWidth: 30
        implicitHeight: 30
        color: "light gray"
        border.color: {
            if (axesSizeSpinbox.activeFocus) {
                if (invertTheme)
                    return "yellow"
                else
                    return "blue"
            }
            else {
                return "light gray"
            }
        }
        border.width: axesSizeSpinbox.activeFocus ? 2 : 1
        
        Text {
            text: "+"
            font.pixelSize: axesSizeSpinbox.font.pixelSize * 2
            color: fontColor
            anchors.fill: parent
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
    
    down.indicator: Rectangle {
        x: axesSizeSpinbox.mirrored ? parent.width - width : 0
        height: parent.height
        implicitWidth: 30
        implicitHeight: 30
        color: "light gray"
        border.color: {
            if (axesSizeSpinbox.activeFocus) {
                if (invertTheme)
                    return "yellow"
                else
                    return "blue"
            }
            else {
                return "light gray"
            }
        }
        border.width: axesSizeSpinbox.activeFocus ? 2 : 1
        
        Text {
            text: "-"
            font.pixelSize: axesSizeSpinbox.font.pixelSize * 2
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
            if (axesSizeSpinbox.activeFocus) {
                if (invertTheme)
                    return "yellow"
                else
                    return "blue"
            }
            else {
                return "light gray"
            }
        }
        border.width: axesSizeSpinbox.activeFocus ? 2 : 1
    }
}
