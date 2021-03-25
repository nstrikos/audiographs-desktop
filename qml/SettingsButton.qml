import QtQuick 2.12

FocusScope {
    id: settingsButton
    width: 50
    height: 50
    z: 100
    anchors.leftMargin: window.width / 8 - width
    activeFocusOnTab: true
    onActiveFocusChanged: {
        if (activeFocus) {
            borderRect.border.color = "blue"
            borderRect.opacity = 0.5
        }
        else {
            borderRect.border.color = "white"
            borderRect.opacity = 0.0
        }
    }
    Keys.onSpacePressed: anchorChangeState.settingsButtonPressed()
    Keys.onEnterPressed: anchorChangeState.settingsButtonPressed()
    Keys.onReturnPressed: anchorChangeState.settingsButtonPressed()

//    Keys.onPressed: {
//        if (event.key === Qt.Key_F2) {
//            startSoundButtonClicked()
//            event.accepted = true;
//        } else if (event.key === Qt.Key_F11) {
//            graphRect.decStep()
//        } else if (event.key === Qt.Key_F12) {
//            graphRect.incStep()
//        } else if (event.key === Qt.Key_F8) {
//            graphRect.stopPoint()
//        } else if (event.key === Qt.Key_F9) {
//            graphRect.previousPoint()
//        } else if (event.key === Qt.Key_F10) {
//            graphRect.nextPoint()
//        } else if (event.key === Qt.Key_F4) {
//            graphRect.sayXCoordinate()
//        } else if (event.key === Qt.Key_F5) {
//            graphRect.sayYCoordinate()
//        }
//    }

    Rectangle {
        id: borderRect
        anchors.fill: parent
        opacity: 0.0
    }
    
    SettingsIcon {
        anchors.fill: parent
    }
    
    MouseArea {
        anchors.fill: parent
        onPressed: anchorChangeState.settingsButtonPressed()
    }
}
