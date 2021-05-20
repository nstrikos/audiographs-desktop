import QtQuick 2.9

import "GraphCanvasJS.js" as CanvasJS

Canvas {
    id: canvas

    property var ctx
    property var xGridValues: []
    property var yGridValues: []
    property var xGridCoords: []
    property var yGridCoords: []

    property var minX: -10
    property var maxX: 10
    property var minY: -10
    property var maxY: 10

    renderStrategy: Canvas.Immediate

    function updateCanvas(minX, maxX, minY, maxY) {
        if (available)
            CanvasJS.paintCanvas(minX, maxX, minY, maxY)
    }

    onAvailableChanged: updateCanvas(minX, maxX, minY, maxY)
    onWidthChanged: updateCanvas(minX, maxX, minY, maxY)
    onHeightChanged: updateCanvas(minX, maxX, minY, maxY)
}
