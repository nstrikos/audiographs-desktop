import QtQuick 2.12

FocusScope {
    id: controlsButton
    anchors.rightMargin: window.width / 2 - controlsRect.width - width
    z: 100
    width: 50
    height: 50
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
    Keys.onSpacePressed: anchorChangeState.controlsButtonPressed()
    Keys.onEnterPressed: anchorChangeState.controlsButtonPressed()
    Keys.onReturnPressed: anchorChangeState.controlsButtonPressed()

//    Keys.onPressed: {
//        window.keyEvent(event)
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
        onPressed: anchorChangeState.controlsButtonPressed()
    }
}
