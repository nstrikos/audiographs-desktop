import QtQuick 2.12
import QtQuick.Controls 2.12

import "../BeautityRect"
import "./Focus"

import "../SettingsRect/AudioSettings"
//import "../SettingsRect/GraphSettings"

import QtQuick.Dialogs 1.3

Flickable {
    id: controlRectFlickable
    width: parent.width
    anchors.top: controlsTitleBar.bottom
    anchors.topMargin: 40
    anchors.bottom: parent.bottom
    contentHeight: 1970
    clip: true

    property alias textInput: textInput
    property alias textInput2: textInput2
    property alias textInput3: textInput3
    property alias textInput4: textInput4
    property alias textInput5: textInput5
    property alias startSoundButton: startButtonFocusScope.startSoundButton
    property alias startSoundButtonFocusScope: startButtonFocusScope

    property color lineColor: parameters.lineColor
    property color backgroundColor: parameters.backgroundColor
    property color highlightColor: parameters.highlightColor
    property color axesColor: parameters.axesColor
    property color derivativeColor: parameters.derivColor

    ScrollBar.vertical: ScrollBar {
        id: scrollBar
        active: true
    }

    onMovementEnded: scrollBar.active = true

//    onContentYChanged: {
        //        ensureVisible(textInput)
        //        ensureVisible(textInput2)
        //        ensureVisible(textInput3)
        //        ensureVisible(textInput4)
        //        ensureVisible(textInput5)
//    }
    
    function ensureVisible(item) {
        if(!item.focus)
            return
//        scrollBar.active = true
        var ypos = item.mapToItem(contentItem, 0, 0).y
        var ext = item.height + ypos
        if ( ypos < contentY // begins before
                || ypos > contentY + height // begins after
                || ext < contentY // ends before
                || ext > contentY + height) { // ends after
            //            // don't exceed bounds
            contentY = Math.max(0, Math.min(ypos - height + item.height, contentHeight - height))
            //            console.log(item.id, "not visible")
//            item.enabled = false
        } else {
            //            console.log(item.id, "visible")
//            item.enabled = true
        }
    }
    
    Item {
        id: controlsMainRect
        width: parent.width
        anchors.topMargin: 20
        anchors.top: parent.top
        
        Label {
            id: label1
            text: (parent.width > 0) ? "f(x) : " : ""
            anchors.left: parent.left
            anchors.leftMargin: 5
            width: 50
            color: fontColor
        }
        
        CustomTextInput {
            id: textInput
            anchors.left: label1.right
            anchors.verticalCenter: label1.verticalCenter
            anchors.rightMargin: 50
            placeholderText: (parent.width > 0) ? "Function expression" : ""
            onFocusChanged: controlRectFlickable.ensureVisible(textInput)
            Accessible.name: qsTr("Function expression")
            onTextChanged: {
                controlsRect.active = false
                textInput2.text = "-10"
                textInput3.text = "10"
                textInput4.text = "-10"
                textInput5.text = "10"
                window.evaluate()
                controlsRect.active = true
            }
        }

        FocusScope {
            id: clearExpressionFocusScope
            anchors.left: textInput.right
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.top: textInput.top
            anchors.bottom: textInput.bottom
            onFocusChanged: controlRectFlickable.ensureVisible(clearExpressionFocusScope)

            activeFocusOnTab: true
            Accessible.name: qsTr("Clear expression")

            Keys.onSpacePressed: pressed()
            Keys.onEnterPressed: pressed()
            Keys.onReturnPressed: pressed()

            function pressed() {
                textInput.clear()
            }

            Rectangle {
                id: button1
                anchors.fill: parent
                color: bgColor
                border.color: clearExpressionFocusScope.activeFocus ? lightColor : "light gray"
                border.width: clearExpressionFocusScope.activeFocus ? 2 : 1
                property bool checked: true
                property var text: "X"

                signal clicked()

                Text {
                    id: text
                    text: button1.text
                    anchors.centerIn: parent
                    font.pointSize: 24
                    color: fontColor
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: clearExpressionFocusScope.pressed()
                }
            }
        }
        
        Label {
            id: label2
            text: (parent.width > 0) ? "min X : " : ""
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: textInput.bottom
            anchors.topMargin: 40
            width: 50
            color: fontColor
        }
        
        CustomTextInput {
            id: textInput2
            onTextChanged: {
                if (controlsRect.active)
                    evaluate()
            }
            onFocusChanged: controlRectFlickable.ensureVisible(textInput2)
        }
        
        Label {
            id: label3
            text: (parent.width > 0) ? "max X : " : ""
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: textInput2.bottom
            anchors.topMargin: 40
            width: 50
            color: fontColor
        }
        
        CustomTextInput {
            id: textInput3
            anchors.left: label3.right
            anchors.verticalCenter: label3.verticalCenter
            placeholderText: (parent.width > 0) ? "maximum X" : ""
            onFocusChanged: controlRectFlickable.ensureVisible(textInput3)
            Accessible.name: qsTr("Set maximum x")
            onTextChanged: {
                if (controlsRect.active)
                    evaluate()
            }
        }
        
        Label {
            id: label4
            text: (parent.width > 0) ? "min Y : " : ""
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: textInput3.bottom
            anchors.topMargin: 40
            width: 50
            color: fontColor
        }
        
        CustomTextInput {
            id: textInput4
            anchors.left: label4.right
            anchors.verticalCenter: label4.verticalCenter
            placeholderText: (parent.width > 0) ? "minimum Y" : ""
            onFocusChanged: controlRectFlickable.ensureVisible(textInput4)
            Accessible.name: qsTr("Set minimum Y")
            onTextChanged: {
                if (controlsRect.active)
                    evaluate()
            }
        }
        
        Label {
            id: label5
            text: (parent.width > 0) ? "max Y : " : ""
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: textInput4.bottom
            anchors.topMargin: 40
            width: 50
            color: fontColor
        }
        
        CustomTextInput {
            id: textInput5
            anchors.left: label5.right
            anchors.verticalCenter: label5.verticalCenter
            placeholderText: (parent.width > 0) ? "maximum Y" : ""
            onFocusChanged: controlRectFlickable.ensureVisible(textInput5)
            Accessible.name: qsTr("Set maximum Y")
            onTextChanged: {
                if (controlsRect.active)
                    evaluate()
            }
        }
        
        StartButtonFocusScope {
            id: startButtonFocusScope
            onFocusChanged: controlRectFlickable.ensureVisible(startButtonFocusScope)
        }

        Focus1 {
            id: focus1
            onFocusChanged: controlRectFlickable.ensureVisible(focus1)
        }

        Focus2 {
            id: focus2
            onFocusChanged: controlRectFlickable.ensureVisible(focus2)
        }

        Focus3 {
            id: focus3
            onFocusChanged: controlRectFlickable.ensureVisible(focus3)
        }

        Focus4 {
            id: focus4
            onFocusChanged: controlRectFlickable.ensureVisible(focus4)
        }

        Focus5 {
            id: focus5
            onFocusChanged: controlRectFlickable.ensureVisible(focus5)
        }

        Focus6 {
            id: focus6
            onFocusChanged: controlRectFlickable.ensureVisible(focus6)
        }

        Focus7 {
            id: focus7
            onFocusChanged: controlRectFlickable.ensureVisible(focus7)
        }

        Focus8 {
            id: focus8
            onFocusChanged: controlRectFlickable.ensureVisible(focus8)
        }

        Focus9 {
            id: focus9
            onFocusChanged: controlRectFlickable.ensureVisible(focus9)
        }

        Focus10 {
            id: focus10
            onFocusChanged: controlRectFlickable.ensureVisible(focus10)
        }

        Focus11 {
            id: focus11
            onFocusChanged: controlRectFlickable.ensureVisible(focus11)
        }

        Focus12 {
            id: focus12
            onFocusChanged: controlRectFlickable.ensureVisible(focus12)
        }

        Focus13 {
            id: focus13
            onFocusChanged: controlRectFlickable.ensureVisible(focus13)
        }

        Focus14 {
            id: focus14
            onFocusChanged: controlRectFlickable.ensureVisible(focus14)
        }

        Focus15 {
            id: focus15
            onFocusChanged: controlRectFlickable.ensureVisible(focus15)
        }

        Focus16 {
            id: focus16
            onFocusChanged: controlRectFlickable.ensureVisible(focus16)
        }

        Label1 {
            id: audioLabel1
            anchors.top: focus16.bottom
        }
        DurationSpinbox {
            id: durationSpinbox
            onFocusChanged: controlRectFlickable.ensureVisible(durationSpinbox)
        }
        Label2 {
            id: audioLabel2
        }
        MinFreqSpinbox {
            id: minFreqSpinbox
            onFocusChanged: controlRectFlickable.ensureVisible(minFreqSpinbox)
        }
        Label3 {
            id: audioLabel3
        }
        MaxFreqSpinbox {
            id: maxFreqSpinbox
            onFocusChanged: controlRectFlickable.ensureVisible(maxFreqSpinbox)
        }
        Label {
            id: audioLabel4
            text: qsTr("Precision digits") + ":"
            anchors.top: audioLabel3.bottom
            anchors.topMargin: 30
            anchors.left: parent.left
            anchors.leftMargin: 10
            width: 80
            height: 15
            color: fontColor
        }

        PrecisionSpinbox {
            id: precisionSpinbox
            onFocusChanged: controlRectFlickable.ensureVisible(precisionSpinbox)
        }

        Label4 {
            id: audioLabel5
        }
        UseNotesFocusScope {
            id: useNotesFocusScope
            onFocusChanged: controlRectFlickable.ensureVisible(useNotesFocusScope)
        }
        Label6 {
            id: audioLabel6
        }
        UseDifferentNotesFocusScope {
            id: useDifferentNotesFocusScope
            onFocusChanged: controlRectFlickable.ensureVisible(useDifferentNotesFocusScope)
        }
        Label5 {
            id: audioLabel7
        }
        ExploreModeFocusScope {
            id: exploreModeFocusScope
            onFocusChanged: controlRectFlickable.ensureVisible(exploreModeFocusScope)
        }
        ResetButton {
            id: resetButton
            onFocusChanged: controlRectFlickable.ensureVisible(resetButton)
        }

        ColorDialog {
            id: colorDialog
            property var request
            onAccepted: {
                if (request === "line color") {
                    parameters.lineColor = color
                    lineColor = color
                    graphRect.curveColor = color
                } else if (request === "background color") {
                    parameters.backgroundColor = color
                    backgroundColor = color
                    graphRect.updateCanvas()
                } else if (request === "axes color") {
                    parameters.axesColor = color
                    axesColor = color
                    graphRect.updateCanvas()
                } else if (request === "highlight color") {
                    parameters.highlightColor = color
                    highlightColor = color
                    graphRect.highlightColor = color
                } else if (request === "derivative color") {
                    parameters.derivColor = color
                    derivativeColor = color
                    graphRect.derivativeColor = color
                }
            }
        }

        function openColorDialog(request) {
            if (request === "line color") {
                colorDialog.color = parameters.lineColor
            } else if (request === "background color") {
                colorDialog.color = parameters.backgroundColor
            } else if (request === "axes color") {
                colorDialog.color = parameters.axesColor
            } else if (request === "highlight color") {
                colorDialog.color = parameters.highlightColor
            } else if (request === "derivative color") {
                colorDialog.color = parameters.derivColor
            }

            colorDialog.request = request
            colorDialog.open()
        }

        GraphLabel1 {
            id: graphLabel1
        }
        GraphColorFocusScope {
            id: graphColorFocusScope
        }
        GraphLabel2 {
            id: graphLabel2
        }
        BackgroundColorFocusScope {
            id: backgroundColorFocusScope
        }
        GraphLabel3 {
            id: graphLabel3
        }
        LineWidthSpinbox {
            id: lineWidthSpinbox
        }
        GraphLabel4 {
            id: graphLabel4
        }
        HighlightColorFocusScope {
            id: highlightColorFocusScope
        }
        GraphLabel5 {
            id: graphLabel5
        }
        HighlightSizeSpinbox {
            id: highlightSizeSpinbox
        }
    }



    Component.onCompleted: {
        scrollBar.position = 0
    }
}
