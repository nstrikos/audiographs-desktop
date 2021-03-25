import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

FocusScope {
    id: showAxesFocusScope
    height: 30
    width: 100
    anchors.verticalCenter: label8.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    property alias color: showAxesCheckBox.color
    property alias showAxesCheckBox: showAxesCheckBox
    activeFocusOnTab: true
    Accessible.name: qsTr("Show grid")
    Keys.onSpacePressed: showAxesCheckBox.checked = ! showAxesCheckBox.checked
    Keys.onEnterPressed: showAxesCheckBox.checked = ! showAxesCheckBox.checked
    Keys.onReturnPressed: showAxesCheckBox.checked = ! showAxesCheckBox.checked
    
    Rectangle {
        id: showAxesCheckBox
        anchors.fill: parent
        color: bgColor
        border.color: showAxesFocusScope.activeFocus ? lightColor : "light gray"
        border.width: showAxesFocusScope.activeFocus ? 2 : 1
        property bool checked: parameters.showAxes
        Text {
            text: showAxesCheckBox.checked ? qsTr("On") : qsTr("Off")
            anchors.centerIn: parent
            font.pointSize: 16
            color: fontColor
        }
        
        MouseArea {
            anchors.fill: parent
            onPressed: {
                showAxesCheckBox.checked = ! showAxesCheckBox.checked
            }
        }
        onCheckedChanged: {
            window.stopAudio()
            parameters.showAxes = checked
            graphRect.graphCanvas.updateCanvas()
        }
    }
}
