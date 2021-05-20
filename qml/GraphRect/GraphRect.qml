import QtQuick 2.12
//import Curve 1.0
//import CurveMovingPoint 1.0
import DisplayView 1.0
import PointView 1.0

import "../BeautityRect"

Rectangle {
    id: graphRect
    z: 10
    color: "white"

    layer.enabled: true
    layer.samples: 256

    property var minX: -10
    property var maxX: 10
    property var minY: -10
    property var maxY: 10

    property alias displayView: displayView
    property alias pointView: pointView
    property alias derivativeView: derivativeView

    property var graphCanvas: graphCanvas
    property color curveColor: parameters.lineColor
    property var curveWidth: parameters.lineWidth
    property color highlightColor: parameters.highlightColor
    property color derivativeColor: parameters.derivColor
    property var highlightSize: parameters.highlightSize

    onCurveColorChanged: displayView.color = curveColor
    onCurveWidthChanged: displayView.lineWidth = curveWidth
    onHighlightColorChanged: pointView.color = highlightColor
    onDerivativeColorChanged: derivativeView.color = derivativeColor
    onHighlightSizeChanged: pointView.size = highlightSize

    GraphCanvas {
        id: graphCanvas
        anchors.fill: parent
    }

    DisplayView {
        id: derivativeView
        objectName: "derivativeView"
        anchors.fill: parent
        visible: true
        layer.enabled: true
        layer.samples: 256
        color: "blue"
        lineWidth: parameters.lineWidth
    }

    DisplayView {
        id: displayView
        objectName: "displayView"
        anchors.fill: parent
        visible: true
        layer.enabled: true
        layer.samples: 256
        color: parameters.lineColor
        lineWidth: parameters.lineWidth
    }

    PointView {
        id: pointView
        objectName: "pointView"
        anchors.fill: parent
        layer.enabled: true
        layer.samples: 256
        color: parameters.highlightColor
        size: parameters.highlightSize
    }

    PinchArea {
        anchors.fill: parent
        onPinchStarted: {
            functionExpression.startPinch()
        }
        onPinchUpdated: {
            functionExpression.pinch(pinch.scale)
        }
        MouseArea {
            anchors.fill: parent
            onWheel: {
                if (!parameters.exploreMode) {
                    //window.newGraph()
                    if (window.canZoomDrag) {
                        functionExpression.setDerivativeMode(0)
                        window.graphRect.derivativeView.setUpdate(false);
                        window.graphRect.derivativeView.visible = false
                        functionExpression.zoom(wheel.angleDelta.y)
                    }
                }
            }
            onPressedChanged: {
                if (!parameters.exploreMode) {
                    if (pressed)
                        if (window.canZoomDrag) {
                            functionExpression.setDerivativeMode(0)
                            window.graphRect.derivativeView.setUpdate(false);
                            window.graphRect.derivativeView.visible = false
                            functionExpression.startDrag(mouseX, mouseY)
                        }
                } else {
                    if (!pressed)
                        functionController.stopAudio()
                }
            }
            onPositionChanged: {
                if (!parameters.exploreMode) {
                    if (pressed)
                        if (window.canZoomDrag) {
                            functionExpression.setDerivativeMode(0)
                            window.graphRect.derivativeView.setUpdate(false);
                            window.graphRect.derivativeView.visible = false
                            functionExpression.drag(mouseX, mouseY, width, height)
                        }
                } else {
                    if (pressed)
                        functionController.mousePoint(mouseX)
                }
            }
        }
    }

    onWidthChanged: updateCanvas()
    onHeightChanged: updateCanvas()

    function updateCanvas() {
        window.stopAudio()
        graphCanvas.updateCanvas(minX, maxX, minY, maxY)
        //functionController.viewDimensionsChanged()
        displayView.updateView()
        derivativeView.updateView()
    }

//    BeautifyGraphRect {

//    }

//    BeautifyGraphRect {
//        anchors.top: parent.top
//        anchors.bottom: undefined
//        height: 8
//        visible: (settingsRect.height > 0) && (!anchorToLeft)

//        gradient: Gradient {
//            GradientStop {
//                color: Qt.rgba(0, 0, 0, 0.4)
//                position: 0
//            }
//            GradientStop {
//                color: Qt.rgba(0, 0, 0, 0.15)
//                position: 0.5
//            }
//            GradientStop {
//                color: Qt.rgba(0, 0, 0, 0)
//                position: 1
//            }
//        }
//    }

//    BeautifyRect {
//        visible: (settingsRect.width > 0)
//    }
}
