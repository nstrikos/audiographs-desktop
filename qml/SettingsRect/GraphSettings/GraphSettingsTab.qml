import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

Rectangle {
    property bool invertTheme: parameters.invertTheme

    property color fontColor:  parameters.invertTheme ? "white" : "black"
    property color lightColor: parameters.invertTheme ? "yellow" : "blue"
    onInvertThemeChanged: {
        fontColor = parameters.invertTheme ? "white" : "black"
        bgColor = !parameters.invertTheme ? "white" : "black"
        lightColor = parameters.invertTheme ? "yellow" : "blue"
    }

    property color bgColor: !parameters.invertTheme ? "white" : "black"

    color: bgColor

    ColorDialog {
        id: colorDialog
        property var request
        onAccepted: {
            if (request === "line color") {
                parameters.lineColor = color
                lineColor = color
                graphRect.curveColor = color
            } else if (request === "background color") {
                parameters.backgroundColor = color
                backgroundColor = color
                graphRect.graphCanvas.updateCanvas()
            } else if (request === "axes color") {
                parameters.axesColor = color
                axesColor = color
                graphRect.graphCanvas.updateCanvas()
            } else if (request === "highlight color") {
                parameters.highlightColor = color
                highlightColor = color
                graphRect.highlightColor = color
            }
        }
    }

    function openColorDialog(request) {
        if (request === "line color") {
            colorDialog.color = parameters.lineColor
        } else if (request === "background color") {
            colorDialog.color = parameters.backgroundColor
        } else if (request === "axes color") {
            colorDialog.color = parameters.axesColor
        } else if (request === "highlight color") {
            colorDialog.color = parameters.highlightColor
        }

        colorDialog.request = request
        colorDialog.open()
    }

    Flickable {
        anchors.fill: parent
        contentHeight: 800
        clip: true
        Label1 {
            id: label1
        }
        GraphColorFocusScope {
            id: graphColorFocusScope
        }
        Label2 {
            id: label2
        }
        BackgroundColorFocusScope {
            id: backgroundColorFocusScope
        }
        Label3 {
            id: label3
        }
        LineWidthSpinbox {
            id: lineWidthSpinbox
        }
        Label4 {
            id: label4
        }
        HighlightColorFocusScope {
            id: highlightColorFocusScope
        }
        Label5 {
            id: label5
        }
        HighlightSizeSpinbox {
            id: highlightSizeSpinbox
        }
        Label6 {
            id: label6
        }
        AxesColorFocusScope {
            id: axesColorFocusScope
        }
        Label7 {
            id: label7
        }
        AxesSizeSpinbox {
            id: axesSizeSpinbox
        }
        Label8 {
            id: label8
        }
        ShowAxesFocusScope {
            id: showAxesFocusScope
        }
        Label9 {
            id: label9
        }
        InvertThemeFocusScope {
            id: invertThemeFocusScope
        }
        ResetButton {
            id: resetButton
        }
    }
}
