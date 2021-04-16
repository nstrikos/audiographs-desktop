import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

Button {
    id: resetButton
    text: qsTr("Reset")
    anchors.top: label9.bottom
    anchors.topMargin: 30
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.leftMargin: 10
    anchors.rightMargin: 10
    width: 80
    height: 50
    Accessible.name: qsTr("Reset graph settings")
    
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
        color: bgColor
        radius: 2
        border.color: resetButton.activeFocus ? lightColor : "light gray"
        border.width: resetButton.activeFocus ? 2 : 1
    }
    onClicked: {
        window.stopAudio()
        parameters.reset()
        lineColor = parameters.lineColor
        graphRect.curveColor = parameters.lineColor
        backgroundColor = parameters.backgroundColor
        graphRect.curveWidth = parameters.lineWidth
        lineWidthSpinbox.value = parameters.lineWidth
        highlightColor = parameters.highlightColor
        graphRect.highlightColor = parameters.highlightColor
        axesColorFocusScope.axesColorRect.color = parameters.axesColor
        axesSizeSpinbox.value = parameters.axesSize
        showAxesFocusScope.showAxesCheckBox.checked = parameters.showAxes
        graphRect.updateCanvas()
        invertThemeFocusScope.invertThemeCheckBox.checked = parameters.invertTheme
        window.setColor()
    }
}
