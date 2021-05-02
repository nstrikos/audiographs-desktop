import QtQuick 2.12
import QtQuick.Controls 2.12

import "../BeautityRect"

TextField {
    id: textInput2
    anchors.left: label2.right
    anchors.leftMargin: 10
    anchors.verticalCenter: label2.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    placeholderText: (parent.width > 0) ? "minimum X" : ""
    height: 50
    selectByMouse: true
    onFocusChanged: ensureVisible(textInput2)
    color: fontColor
    background: Rectangle {
        id: backRect2
        color: controlsRect.color
        border.color: {
            if (textInput2.activeFocus) {
                if (invertTheme)
                    return "yellow"
                else
                    return "blue"
            } else {
                return "light gray"
            }
        }
        border.width: textInput2.activeFocus ? 2 : 1
    }
    Accessible.name: qsTr("Set minimum x")

    onCursorPositionChanged: {
        if (activeFocus) {
            var res = text.substring(cursorPosition - 1, cursorPosition)
            textToSpeech.speak( textToSpeech.normalizeText((res) ) )
        }
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_X  && event.modifiers & Qt.ControlModifier) {
            window.sayX()
            event.accepted = true;
        } else if (event.key === Qt.Key_Y  && event.modifiers & Qt.ControlModifier) {
            window.sayY()
            event.accepted = true;
        } else if (event.key === Qt.Key_PageDown) {
            window.previousPoint()
            event.accepted = true;
        } else if (event.key === Qt.Key_PageUp) {
            window.nextPoint()
            event.accepted = true;
        } else if (event.key === Qt.Key_Left  && event.modifiers & Qt.ControlModifier) {
            window.previousPointInterest()
            event.accepted = true;
        } else if (event.key === Qt.Key_Right  && event.modifiers & Qt.ControlModifier) {
            window.nextPointInterest()
            event.accepted = true;
        } else if (event.key === Qt.Key_Left  && event.modifiers & Qt.ShiftModifier) {
            window.previousFast()
            event.accepted = true;
        } else if (event.key === Qt.Key_Right  && event.modifiers & Qt.ShiftModifier) {
            window.nextFast()
            event.accepted = true;
        } else if (event.key === Qt.Key_Home) {
            window.firstPoint()
            event.accepted = true;
        } else if (event.key === Qt.Key_End) {
            window.lastPoint()
            event.accepted = true;
        } else if (event.key === Qt.Key_D  && event.modifiers & Qt.ControlModifier) {
            window.sayDerivative()
            event.accepted = true;
        } else if (event.key === Qt.Key_0  && event.modifiers & Qt.ControlModifier) {
            window.normalDerivative()
            event.accepted = true;
        } else if (event.key === Qt.Key_1  && event.modifiers & Qt.ControlModifier) {
            window.firstDerivative()
            event.accepted = true;
        } else if (event.key === Qt.Key_2  && event.modifiers & Qt.ControlModifier) {
            window.secondDerivative()
            event.accepted = true;
        } else if (event.key === Qt.Key_BracketLeft  && event.modifiers & Qt.ControlModifier) {
            functionExpression.decStep()
            event.accepted = true;
        } else if (event.key === Qt.Key_BracketRight  && event.modifiers & Qt.ControlModifier) {
            functionExpression.incStep()
            event.accepted = true;
        }
    }
}
