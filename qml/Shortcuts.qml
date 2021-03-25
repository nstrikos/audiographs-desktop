import QtQuick 2.0

import QtQuick 2.12

Item {
    Shortcut {
        sequence: "Esc"
        onActivated: close()
    }
    Shortcut {
        sequence: "F2"
        onActivated: window.playPressed()
    }
    Shortcut {
        sequence: "Ctrl+Space"
        onActivated: window.playPressed()
    }
    Shortcut {
        sequence: "Shift+F2"
        onActivated: {
            controlsRect.textInput.clear()
            controlsRect.textInput.forceActiveFocus()
        }
    }
    Shortcut {
        sequence: "F3"
        onActivated: {
            window.stopAudio()
            functionController.sayXCoordinate()
        }
    }
    Shortcut {
        sequence: "Ctrl+Down"
        onActivated: {
            window.stopAudio()
            functionController.sayXCoordinate()
        }
    }
    Shortcut {
        sequence: "F4"
        onActivated: {
            window.stopAudio()
            functionController.sayYCoordinate()
        }
    }
    Shortcut {
        sequence: "Ctrl+Up"
        onActivated: {
            window.stopAudio()
            functionController.sayYCoordinate()
        }
    }
    Shortcut {
        sequence: "F5"
        onActivated: {
            window.explore
            functionController.previousPointX();
        }
    }
    Shortcut {
        sequence: "F6"
        onActivated: {
            window.explore
            functionController.nextPointX();
        }
    }
    Shortcut {
        sequence: "Shift+F5"
        onActivated: {
            window.explore
            functionController.previousPointY();
        }
    }
    Shortcut {
        sequence: "Shift+F6"
        onActivated: {
            window.explore
            functionController.nextPointY();
        }
    }

    Shortcut {
        sequence: "Shift+F7"
        onActivated: {
            window.interestingPoint()
            functionController.previousPointInterestFast()
        }
    }
    Shortcut {
        sequence: "F7"
        onActivated: {
            window.interestingPoint()
            functionController.previousPointInterest()
        }
    }
    Shortcut {
        sequence: "Ctrl+Left"
        onActivated: {
            window.interestingPoint()
            functionController.previousPointInterest()
        }
    }
    Shortcut {
        sequence: "Shift+F8"
        onActivated: {
            window.interestingPoint()
            functionController.nextPointInterestFast()
        }
    }
    Shortcut {
        sequence: "F8"
        onActivated: {
            window.interestingPoint()
            functionController.nextPointInterest()
        }
    }
    Shortcut {
        sequence: "Ctrl+Right"
        onActivated: {
            window.interestingPoint()
            functionController.nextPointInterest()
        }
    }
    Shortcut {
        sequence: "F9"
        onActivated: {
            window.explore()
            functionController.previousPoint()
        }
    }
    Shortcut {
        sequence: "F10"
        onActivated: {
            window.explore()
            functionController.nextPoint()
        }
    }
    Shortcut {
        sequence: "F11"
        onActivated: {
            functionController.decStep()
        }
    }
    Shortcut {
        sequence: "F12"
        onActivated: {
            functionController.incStep()
        }
    }
    Shortcut {
        sequence: StandardKey.MoveToPreviousPage
        onActivated: {
            functionController.firstPoint()
        }
    }
    Shortcut {
        sequence: StandardKey.MoveToNextPage
        onActivated: {
            functionController.endPoint()
        }
    }
    Shortcut {
        sequence: "Ctrl+F12"
        onActivated: {
            window.settingsRect.audioSettingsTab.useNotesFocusScope.useNotesCheckBox.checked = !window.settingsRect.audioSettingsTab.useNotesFocusScope.useNotesCheckBox.checked
        }
    }

    Shortcut {
        sequence: "Ctrl+D"
        onActivated: {
            functionController.setMode()
        }
    }

    //    onActiveFocusItemChanged: {
    //        if (activeFocusItem == controlsRect.textInput)
    //            print("focus: textInput")
    //        else if (activeFocusItem == controlsRect.textInput2)
    //            print("focus: textInput2")
    //        else if (activeFocusItem == controlsRect.textInput3)
    //            print("focus: textInput3")
    //        else if (activeFocusItem == controlsRect.textInput4)
    //            print("focus: textInput4")
    //        else if (activeFocusItem == controlsRect.textInput5)
    //            print("focus: textInput5")
    //        else if (activeFocusItem == controlsRect.startSoundButtonFocusScope)
    //            print("focus: startButton")
    //        else if (activeFocusItem == controlsButton)
    //            print("focus: controlsButton")
    //        else if (activeFocusItem == settingsButton)
    //            print("focus: settingsButton")
    //        else if (activeFocusItem == settingsRect)
    //            print("focus: settingsRect")
    //        else
    //            print("which item has focus?")
    //    }

    //        function keyEvent(event) {
    //            if (event.key === Qt.Key_F2) {
    //                if (functionController.validExpression())
    //                    window.playPressed()
    //                else
    //                    textToSpeech.speak(functionController.getError())
    //                event.accepted = true;
    //            } else if (event.key === Qt.Key_F3) {
    //                window.stopAudio()
    //                functionController.sayXCoordinate()
    //            } else if (event.key === Qt.Key_F4) {
    //                window.stopAudio()
    //                functionController.sayYCoordinate()
    //            } else if ((event.key === Qt.Key_F7) && (event.modifiers & Qt.ShiftModifier)) {
    //                window.interestingPoint()
    //                functionController.previousPointInterestFast()
    //            } else if (event.key === Qt.Key_F7) {
    //                window.interestingPoint()
    //                functionController.previousPointInterest()
    //            } else if ((event.key === Qt.Key_F8) && (event.modifiers & Qt.ShiftModifier)) {
    //                window.interestingPoint()
    //                functionController.nextPointInterestFast()
    //            } else if (event.key === Qt.Key_F8) {
    //                window.interestingPoint()
    //                functionController.nextPointInterest()
    //            } else if (event.key === Qt.Key_F9) {
    //                window.explore()
    //                functionController.previousPoint()
    //            } else if (event.key === Qt.Key_F10) {
    //                window.explore()
    //                functionController.nextPoint()
    //            } else if (event.key === Qt.Key_F11) {
    //                functionController.decStep()
    //            } else if (event.key === Qt.Key_F12) {
    //                functionController.incStep()
    //            } else if (event.key === Qt.Key_PageUp) {
    //                functionController.firstPoint()
    //            }
    //        }
}
