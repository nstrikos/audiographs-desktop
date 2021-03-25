import QtQuick 2.12

Item {
    id: myItem

    property int minWidth: 200

    function getWidth() {
        if (window.width / 4 > minWidth)
            return window.width / 4
        else
            return minWidth
    }

    states: [
        State {
            name: "state1"
            AnchorChanges {
                target: controlsRect
                anchors.top: parent.top
                anchors.bottom: parent.bottom
            }
            AnchorChanges {
                target: graphRect
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: controlsRect.right
                anchors.right: parent.right
            }
            AnchorChanges {
                target: settingsRect
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.right
                anchors.right: parent.right
            }
            
            AnchorChanges {
                target: controlsButton
                anchors.top: parent.top
                anchors.right: parent.horizontalCenter
            }
            
            AnchorChanges {
                target: settingsButton
                anchors.top: parent.top
                anchors.right: graphRect.right
            }
            
            PropertyChanges {
                target: controlsRect
                width: getWidth()
            }
            
            PropertyChanges {
                target: settingsRect
                anchors.leftMargin: 0
            }
        },
        State {
            name: "state2"
            
            AnchorChanges {
                target: controlsRect
                anchors.left: parent.left
                anchors.right: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
            }
            
            AnchorChanges {
                target: graphRect
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
            }
            
            AnchorChanges {
                target: settingsRect
                anchors.left: parent.right
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
            }
            
            AnchorChanges {
                target: controlsButton
                anchors.left: graphRect.left
                anchors.top: parent.top
            }
            
            AnchorChanges {
                target: settingsButton
                anchors.right: graphRect.right
                anchors.top: parent.top
            }
            
            PropertyChanges {
                target: controlsRect
                anchors.rightMargin: 0
            }
            
            PropertyChanges {
                target: settingsRect
                anchors.leftMargin: 0
            }
        },
        State {
            name: "state3"
            
            AnchorChanges {
                target: controlsRect
                anchors.left: parent.left
                anchors.right: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
            }
            
            AnchorChanges {
                target: settingsRect
                anchors.left: parent.horizontalCenter
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
            }
            
            AnchorChanges {
                target: controlsButton
                anchors.left: graphRect.left
                anchors.top: parent.top
            }
            
            AnchorChanges {
                target: settingsButton
                anchors.left: parent.horizontalCenter
                anchors.top: parent.top
            }
            
            PropertyChanges {
                target: controlsRect
                anchors.rightMargin: 0
            }
            
            AnchorChanges {
                target: graphRect
                anchors.left: parent.left
                anchors.right: settingsRect.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
            }
        },
        State {
            name: "state4"
            
            AnchorChanges {
                target: graphRect
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.verticalCenter
            }
            
            AnchorChanges {
                target: controlsRect
                anchors.top: graphRect.bottom
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
            }
            
//            AnchorChanges {
//                target: settingsRect
//                anchors.top: parent.top
//                anchors.bottom: graphRect.top
//                anchors.left: parent.left
//                anchors.right: parent.right
//            }
            
            PropertyChanges {
                target: settingsRect
                //height: 0
//                visible: true
                z: controlsRect.z - 1
            }
            
            PropertyChanges {
                target: controlsRect
                anchors.rightMargin: 0
            }
            
            PropertyChanges {
                target: controlsButton
                anchors.rightMargin: 0
            }
            
            PropertyChanges {
                target: settingsRect
                anchors.leftMargin: 0
            }
            
            AnchorChanges {
                target: controlsButton
                anchors.bottom: graphRect.bottom
                anchors.right: graphRect.right
            }
            
            AnchorChanges {
                target: settingsButton
                anchors.top: graphRect.top
                anchors.right: graphRect.right
            }
        },
        State {
            name: "state5"
            
            AnchorChanges {
                target: graphRect
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
            }
            
            AnchorChanges {
                target: controlsRect
                anchors.top: graphRect.bottom
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
            }
            
            AnchorChanges {
                target: settingsRect
                anchors.top: parent.top
                anchors.bottom: graphRect.top
                anchors.left: parent.left
                anchors.right: parent.right
            }
            
            PropertyChanges {
                target: settingsRect
                height: 0
            }
            
            PropertyChanges {
                target: controlsRect
                anchors.rightMargin: 0
            }
            
            PropertyChanges {
                target: controlsButton
                anchors.rightMargin: 0
            }
            
            PropertyChanges {
                target: settingsRect
                anchors.leftMargin: 0
            }
            
            AnchorChanges {
                target: controlsButton
                anchors.bottom: graphRect.bottom
                anchors.right: graphRect.right
            }
            
            AnchorChanges {
                target: settingsButton
                anchors.top: graphRect.top
                anchors.right: graphRect.right
            }
        },
        State {
            name: "state6"
            
            AnchorChanges {
                target: settingsRect
                anchors.top: parent.top
                anchors.bottom: parent.verticalCenter
                anchors.left: parent.left
                anchors.right: parent.right
            }
            
            AnchorChanges {
                target: graphRect
                anchors.top: settingsRect.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
            }
            
            AnchorChanges {
                target: controlsRect
                anchors.top: graphRect.bottom
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
            }
            
            AnchorChanges {
                target: controlsButton
                anchors.bottom: graphRect.bottom
                anchors.right: graphRect.right
            }
            
            AnchorChanges {
                target: settingsButton
                anchors.top: graphRect.top
                anchors.right: graphRect.right
            }
            
            PropertyChanges {
                target: controlsRect
                anchors.rightMargin: 0
            }
            
            PropertyChanges {
                target: controlsButton
                anchors.rightMargin: 0
            }
            
            PropertyChanges {
                target: settingsRect
                anchors.leftMargin: 0
            }
        }
    ]

    function controlsButtonPressed() {
//        controlsRect.stopAudio()
        if (state == 'state1') {
            state = 'state2'
        }
        else if (state == 'state2' || state == 'state3') {
            state = 'state1'
        }
        else if (state == 'state4') {
            state = 'state5'
        }
        else if (state == 'state5' || state == 'state6')
            state = 'state4'
    }

    function settingsButtonPressed() {
//        controlsRect.stopAudio()
        if (state == 'state1' || state == 'state2')
            state = 'state3'
        else if (state == 'state3')
            state = 'state2'
        else if (state == 'state4' || state == 'state5')
            state = 'state6'
        else if (state == 'state6')
            state = 'state5'
    }

    function anchorChanged() {
//        controlsRect.stopAudio()
        if (anchorToLeft == false) {
            if (state == 'state1')
                state = 'state4'
            else if (state == 'state2')
                state = 'state5'
            else if (state == 'state3')
                state = 'state6'
        } else if (anchorToLeft == true) {
            if (state == 'state4')
                state = 'state1'
            else if (state == 'state5')
                state = 'state2'
            else if (state == 'state6')
                state = 'state3'
        }
    }
}
