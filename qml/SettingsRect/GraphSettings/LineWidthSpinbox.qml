import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

SpinBox {
    id: lineWidthSpinbox
    height: 30
    width: 100
    anchors.verticalCenter: label3.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    from: 1
    to: 10
    value: parameters.lineWidth
    Accessible.name: qsTr("Line width")
    onValueChanged: {
        window.stopAudio()
        graphRect.curveWidth = value
        parameters.lineWidth = value
    }
    editable: false
    
    contentItem: TextInput {
        z: 2
        text: lineWidthSpinbox.textFromValue(lineWidthSpinbox.value, lineWidthSpinbox.locale)
        
        font: lineWidthSpinbox.font
        color: fontColor
        selectionColor: "#21be2b"
        selectedTextColor: "#ffffff"
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        
        readOnly: !lineWidthSpinbox.editable
        validator: lineWidthSpinbox.validator
        inputMethodHints: Qt.ImhFormattedNumbersOnly
    }
    
    up.indicator: Rectangle {
        x: lineWidthSpinbox.mirrored ? 0 : parent.width - width
        height: parent.height
        implicitWidth: 30
        implicitHeight: 30
        color: "light gray"
        border.color: {
            if (lineWidthSpinbox.activeFocus) {
                if (invertTheme)
                    return "yellow"
                else
                    return "blue"
            }
            else {
                return "light gray"
            }
        }
        border.width: lineWidthSpinbox.activeFocus ? 2 : 1
        
        Text {
            text: "+"
            font.pixelSize: lineWidthSpinbox.font.pixelSize * 2
            color: fontColor
            anchors.fill: parent
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
    
    down.indicator: Rectangle {
        x: lineWidthSpinbox.mirrored ? parent.width - width : 0
        height: parent.height
        implicitWidth: 30
        implicitHeight: 30
        color: "light gray"
        border.color: {
            if (lineWidthSpinbox.activeFocus) {
                if (invertTheme)
                    return "yellow"
                else
                    return "blue"
            }
            else {
                return "light gray"
            }
        }
        border.width: lineWidthSpinbox.activeFocus ? 2 : 1
        
        Text {
            text: "-"
            font.pixelSize: lineWidthSpinbox.font.pixelSize * 2
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
            if (lineWidthSpinbox.activeFocus) {
                if (invertTheme)
                    return "yellow"
                else
                    return "blue"
            }
            else {
                return "light gray"
            }
        }
        border.width: lineWidthSpinbox.activeFocus ? 2 : 1
    }
}
