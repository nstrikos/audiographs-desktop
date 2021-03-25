import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.3

import "AudioSettings"
import "GraphSettings"

Rectangle {
    id: settingsRect
    anchors.leftMargin: window.width / 8

    property color lineColor: parameters.lineColor
    property color backgroundColor: parameters.backgroundColor
    property color highlightColor: parameters.highlightColor
    property color axesColor: parameters.axesColor

    property alias audioSettingsTab: audioSettingsTab

    TabBar {
        id: bar
        width: parent.width
        TabButton {
            text: qsTr("Audio")
        }
        TabButton {
            text: qsTr("Graph")
        }
    }

    StackLayout {
        width: parent.width
        anchors.top: bar.bottom
        anchors.bottom: parent.bottom
        currentIndex: bar.currentIndex
        AudioSettingsTab {
            id: audioSettingsTab
        }
        GraphSettingsTab {
            id: graphSettingsTab
        }
        Item {
            id: activityTab
        }
    }  
}
