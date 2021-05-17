import QtQuick 2.0

import QtQuick 2.12

Item {
//    Shortcut {
//        sequence: "Esc"
//        onActivated: close()
//    }
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
            textToSpeech.speak(qsTr("Function expression"))
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
        sequence: "Shift+Left"
        onActivated: {
            window.previousFast()
        }
    }
    Shortcut {
        sequence: "Shift+Right"
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
        sequence: "Ctrl+D"
        onActivated: {
            window.sayDerivative()
        }
    }

    Shortcut {
        sequence: "Ctrl+0"
        onActivated: {
            window.normalDerivative()
        }
    }

    Shortcut {
        sequence: "Ctrl+1"
        onActivated: {
            window.firstDerivative()
        }
    }

    Shortcut {
        sequence: "Ctrl+2"
        onActivated: {
            window.secondDerivative()
        }
    }

    Shortcut {
        sequence: "Ctrl+["
        onActivated: {
            functionExpression.decStep()
        }
    }
    Shortcut {
        sequence: "Ctrl+]"
        onActivated: {
            functionExpression.incStep()
        }
    }
    Shortcut {
        sequence: "F3"
        onActivated: {
            window.controlsRect.useNotesFocusScope.useNotesCheckBox.checked = !window.controlsRect.useNotesFocusScope.useNotesCheckBox.checked
        }
    }
    Shortcut {
        sequence: "F4"
        onActivated: {
            window.controlsRect.useNegativeNotesFocusScope.useDifferentNotesCheckBox.checked= !window.controlsRect.useNegativeNotesFocusScope.useDifferentNotesCheckBox.checked
        }
    }
}
