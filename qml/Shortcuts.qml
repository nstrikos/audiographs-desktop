import QtQuick 2.0

import QtQuick 2.12

Item {
    Shortcut {
        sequence: "Esc"
        onActivated: close()
    }
    Shortcut {
        sequence: "Return"
        onActivated: {
            window.playPressed()
        }
    }
    Shortcut {
        sequence: "Ctrl+N"
        onActivated: {
            controlsRect.textInput.clear()
            controlsRect.textInput.forceActiveFocus()
            window.evaluate()
        }
    }
    Shortcut {
        sequence: "Ctrl+X"
        onActivated: {
            window.sayX()
        }
    }
    Shortcut {
        sequence: "Ctrl+Y"
        onActivated: {
            window.sayY()
        }
    }
    Shortcut {
        sequence: StandardKey.MoveToPreviousPage
        onActivated: {
            window.nextPoint()
        }
    }
    Shortcut {
        sequence: StandardKey.MoveToNextPage
        onActivated: {
            window.previousPoint()
        }
    }
    Shortcut {
        sequence: "Ctrl+Left"
        onActivated: {
            window.previousPointInterest()
        }
    }
    Shortcut {
        sequence: "Ctrl+Right"
        onActivated: {
            window.nextPointInterest()
        }
    }
    Shortcut {
        sequence: "Alt+Left"
        onActivated: {
            window.previousFast()
        }
    }
    Shortcut {
        sequence: "Alt+Right"
        onActivated: {
            window.nextFast()
        }
    }
    Shortcut {
        sequence: StandardKey.MoveToStartOfDocument
        onActivated: {
            window.firstPoint()
        }
    }
    Shortcut {
        sequence: StandardKey.MoveToEndOfDocument
        onActivated: {
            window.lastPoint()
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
}
