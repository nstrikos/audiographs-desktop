import QtQuick 2.12
import QtQuick.Window 2.12

import QtQml.StateMachine 1.0 as DSM

//Item {
//    DSM.StateMachine {
//        id: stateMachine
//        initialState: initialState
//        running: true
//        DSM.State {
//            id: initialState
//            DSM.SignalTransition {
//                targetState: evaluateState
//                signal: window.evaluate
//            }
//            DSM.SignalTransition {
//                targetState: errorDisplayState
//                signal: window.playPressed
//            }
//            onEntered: {
//                console.log("initial state")
//                controlsRect.startSoundButton.enabled = false
//            }
//        }
//        DSM.State {
//            id: errorDisplayState
//            DSM.SignalTransition {
//                targetState: initialState
//                signal: window.init
//            }
//            onEntered: {
//                console.log("error state")
//                window.showError(functionController.getError())
//            }
//        }

//        DSM.State {
//            id: evaluateState
//            DSM.SignalTransition {
//                targetState: initialState
//                signal: error
//            }
//            DSM.SignalTransition {
//                targetState: graphReadyState
//                signal: newGraph
//            }
//            onEntered: {
//                console.log("evaluate state")
//                functionExpression.calculate(controlsRect.textInput.text,
//                                                   controlsRect.textInput2.text,
//                                                   controlsRect.textInput3.text,
//                                                   controlsRect.textInput4.text,
//                                                   controlsRect.textInput5.text)
//                controlsRect.startSoundButton.enabled = false
//            }
//        }
//        DSM.State {
//            id: graphReadyState
//            DSM.SignalTransition {
//                targetState: evaluateState
//                signal: window.evaluate
//            }
//            DSM.SignalTransition {
//                targetState: initialState
//                signal: error
//            }
//            DSM.SignalTransition {
//                targetState: graphReadyState
//                signal: newGraph
//            }
//            DSM.SignalTransition {
//                targetState: playSoundState
//                signal: playPressed
//            }
//            DSM.SignalTransition {
//                targetState: exploreState//pointState
//                signal: explore
//            }
//            DSM.SignalTransition {
//                targetState: interestingPointState//pointState
//                signal: interestingPoint
//            }
//            onEntered: {
//                console.log("graph ready state")
//                controlsRect.startSoundButton.enabled = true
//                controlsRect.startSoundButton.text = qsTr("Start sound")
//                graphRect.updateCanvas()
//            }
//        }

//        DSM.State {
//            id: playSoundState

//            DSM.SignalTransition {
//                targetState: evaluateState
//                signal: window.evaluate
//            }
//            DSM.SignalTransition {
//                targetState: initialState
//                signal: error
//            }
//            DSM.SignalTransition {
//                targetState: graphReadyState
//                signal: stopAudio
//            }
//            DSM.SignalTransition {
//                targetState: graphReadyState
//                signal: newGraph
//            }
//            DSM.SignalTransition {
//                targetState: graphReadyState
//                signal: playPressed
//            }
//            DSM.SignalTransition {
//                targetState: exploreState//pointState
//                signal: explore
//            }
//            DSM.SignalTransition {
//                targetState: interestingPointState//pointState
//                signal: interestingPoint
//            }
//            onEntered: {
//                console.log("play sound state")
//                controlsRect.startSoundButton.enabled = true
//                controlsRect.startSoundButton.text = qsTr("Stop sound")
//                functionExpression.audio()
//            }
//            onExited: {
//                controlsRect.startSoundButton.text = qsTr("Start sound")
//                functionExpression.stopAudio()
//                functionController.firstPoint()
//            }
//        }

//        DSM.State {
//            id: exploreState
//            DSM.SignalTransition {
//                targetState: evaluateState
//                signal: evaluate
//            }
//            DSM.SignalTransition {
//                targetState: initialState
//                signal: error
//            }
//            DSM.SignalTransition {
//                targetState: playSoundState
//                signal: playPressed
//            }
//            DSM.SignalTransition {
//                targetState: graphReadyState
//                signal: newGraph
//            }
//            DSM.SignalTransition {
//                targetState: interestingPointState
//                signal: interestingPoint
//            }
//            onEntered: {
//                console.log("explore state")
//                functionController.stopAudio()
//            }
//        }
//        DSM.State {
//            id: interestingPointState
//            DSM.SignalTransition {
//                targetState: evaluateState
//                signal: evaluate
//            }
//            DSM.SignalTransition {
//                targetState: graphReadyState
//                signal: playPressed
//            }
//            DSM.SignalTransition {
//                targetState: graphReadyState
//                signal: newGraph
//            }
//            DSM.SignalTransition {
//                targetState: exploreState
//                signal: explore
//            }
//            DSM.SignalTransition {
//                targetState: interestingPointStoppedState
//                signal: interestingPointStopped
//            }
//            onEntered: {
//                console.log("interesting point state")
//                //functionController.stopAudio()
//                controlsRect.startSoundButton.text = qsTr("Stop sound")
//            }
//            onExited: {
//                functionController.stopInterestingPoint()
//                controlsRect.startSoundButton.text = qsTr("Start sound")
//            }
//        }

//        DSM.State {
//            id: interestingPointStoppedState
//            DSM.SignalTransition {
//                targetState: interestingPointState
//                signal: interestingPoint
//            }
//            DSM.SignalTransition {
//                targetState: evaluateState
//                signal: evaluate
//            }
//            DSM.SignalTransition {
//                targetState: playSoundState
//                signal: playPressed
//            }
//            DSM.SignalTransition {
//                targetState: graphReadyState
//                signal: newGraph
//            }
//            DSM.SignalTransition {
//                targetState: exploreState
//                signal: explore
//            }
//            onEntered: {
//                console.log("interesting point stopped state")
//                //functionController.stopAudio()
//                controlsRect.startSoundButton.text = qsTr("Start sound")
//            }
//        }
//    }
//}

Item {
    DSM.StateMachine {
        id: stateMachine
        initialState: initialState
        running: true
        DSM.State {
            id: initialState
            DSM.SignalTransition {
                targetState: evaluateState
                signal: window.evaluate
            }
//            DSM.SignalTransition {
//                targetState: errorDisplayState
//                signal: window.playPressed
//            }
            onEntered: {
                console.log("initial state")
                functionExpression.setDerivativeMode(0)
                window.graphRect.pointView.clear()
                window.graphRect.derivativeView.setUpdate(false);
                window.graphRect.graphCanvas.updateCanvas(-10, 10, -10, 10)
                disableControls()               
            }
        }

        DSM.State {
            id: errorDisplayState
            DSM.SignalTransition {
                targetState: initialState
                signal: window.errorAccepted
            }
            onEntered: {
                console.log("error state")
                //window.showError(functionExpression.getError())
            }
        }

        DSM.State {
            id: evaluateState
            DSM.SignalTransition {
                targetState: initialState
                signal: error
            }
            DSM.SignalTransition {
                targetState: graphReadyState
                signal: newGraph
            }
            onEntered: {
                console.log("evaluate state")
                disableControls()
                functionExpression.setDerivativeMode(0)
                window.graphRect.derivativeView.setUpdate(false);
                window.graphRect.derivativeView.visible = false
                functionExpression.calculate(controlsRect.textInput.text,
                                             controlsRect.textInput2.text,
                                             controlsRect.textInput3.text,
                                             controlsRect.textInput4.text,
                                             controlsRect.textInput5.text)
            }
        }

        DSM.State {
            id: graphReadyState
            DSM.SignalTransition {
                targetState: evaluateState
                signal: window.evaluate
            }
            DSM.SignalTransition {
                targetState: initialState
                signal: error
            }
            DSM.SignalTransition {
                targetState: graphReadyState
                signal: newGraph
            }
            DSM.SignalTransition {
                targetState: playSoundState
                signal: playPressed
            }
            DSM.SignalTransition {
                targetState: exploreState
                signal: explore
            }
            DSM.SignalTransition {
                targetState: interestingPointState
                signal: interestingPoint
            }
            onEntered: {
                console.log("graph ready state")
                enableControls()
                controlsRect.startSoundButton.text = qsTr("Start sound")
                graphRect.updateCanvas()
                window.graphRect.pointView.clear()
            }
        }

        DSM.State {
            id: playSoundState

            DSM.SignalTransition {
                targetState: evaluateState
                signal: window.evaluate
            }

            DSM.SignalTransition {
                targetState: graphReadyState
                signal: stopAudio
            }
            DSM.SignalTransition {
                targetState: graphReadyState
                signal: newGraph
            }
            DSM.SignalTransition {
                targetState: graphReadyState
                signal: playPressed
            }
            DSM.SignalTransition {
                targetState: exploreState
                signal: explore
            }
            DSM.SignalTransition {
                targetState: interestingPointState
                signal: interestingPoint
            }
            onEntered: {
                console.log("play sound state")
                enableControls()
                controlsRect.startSoundButton.text = qsTr("Stop sound")
                functionExpression.audio()
            }
            onExited: {
                controlsRect.startSoundButton.text = qsTr("Start sound")
                functionExpression.stopAudio()
                //window.graphRect.pointView.clear()
            }
        }

        DSM.State {
            id: exploreState
            DSM.SignalTransition {
                targetState: evaluateState
                signal: evaluate
            }

            DSM.SignalTransition {
                targetState: playSoundState
                signal: playPressed
            }
            DSM.SignalTransition {
                targetState: graphReadyState
                signal: newGraph
            }
            DSM.SignalTransition {
                targetState: interestingPointState
                signal: interestingPoint
            }
            onEntered: {
                console.log("explore state")
                //functionController.stopAudio()
                functionExpression.stopAudio()
            }
        }
        DSM.State {
            id: interestingPointState
            DSM.SignalTransition {
                targetState: evaluateState
                signal: evaluate
            }

            DSM.SignalTransition {
                targetState: exploreState
                signal: playPressed
            }
            DSM.SignalTransition {
                targetState: graphReadyState
                signal: newGraph
            }
            DSM.SignalTransition {
                targetState: exploreState
                signal: explore
            }
            DSM.SignalTransition {
                targetState: interestingPointStoppedState
                signal: interestingPointFinished
            }
            onEntered: {
                console.log("interesting point state")
                controlsRect.startSoundButton.text = qsTr("Stop sound")
            }
            onExited: {
                controlsRect.startSoundButton.text = qsTr("Start sound")
                functionExpression.stopAudio()
            }
        }

        DSM.State {
            id: interestingPointStoppedState
            DSM.SignalTransition {
                targetState: evaluateState
                signal: evaluate
            }

            DSM.SignalTransition {
                targetState: exploreState
                signal: playPressed
            }
            DSM.SignalTransition {
                targetState: graphReadyState
                signal: newGraph
            }
            DSM.SignalTransition {
                targetState: exploreState
                signal: explore
            }
            DSM.SignalTransition {
                targetState: interestingPointState
                signal: interestingPoint
            }
            onEntered: {
                console.log("interesting point finished")
                controlsRect.startSoundButton.text = qsTr("Start sound")
            }
        }

    }

    function disableControls()
    {
        controlsRect.startSoundButton.enabled = false
        window.canZoomDrag = false
    }

    function enableControls()
    {
        controlsRect.startSoundButton.enabled = true
        window.canZoomDrag = true
    }
}
