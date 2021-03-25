import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

Rectangle {
    color: bgColor

    property bool invertTheme: parameters.invertTheme

    property color fontColor:  parameters.invertTheme ? "white" : "black"
    property color lightColor: parameters.invertTheme ? "yellow" : "blue"

    onInvertThemeChanged: {
        fontColor = parameters.invertTheme ? "white" : "black"
        bgColor = !parameters.invertTheme ? "white" : "black"
        lightColor = parameters.invertTheme ? "yellow" : "blue"
    }

    property color bgColor: !parameters.invertTheme ? "white" : "black"

    property alias useNotesFocusScope: useNotesFocusScope

    Flickable {
        anchors.fill: parent
        contentHeight: 500
        clip: true
        Label1 {
            id: label1
        }
        DurationSpinbox {
            id: durationSpinbox
        }
        Label2 {
            id: label2
        }
        MinFreqSpinbox {
            id: minFreqSpinbox
        }
        Label3 {
            id: label3
        }
        MaxFreqSpinbox {
            id: maxFreqSpinbox
        }
        Label {
            id: label33
            text: qsTr("Precision digits") + ":"
            anchors.top: label3.bottom
            anchors.topMargin: 30
            anchors.left: parent.left
            anchors.leftMargin: 10
            width: 80
            height: 15
            color: fontColor
        }

        PrecisionSpinbox {
            id: precisionSpinbox
        }

        Label4 {
            id: label4
        }
        UseNotesFocusScope {
            id: useNotesFocusScope
        }
        Label5 {
            id: label5
        }
        ExploreModeFocusScope {
            id: exploreModeFocusScope
        }
        ResetButton {
            id: resetButton
        }
    }
}
