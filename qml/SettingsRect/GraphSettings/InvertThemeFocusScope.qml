import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

FocusScope {
    id: invertThemeFocusScope
    height: 30
    width: 100
    anchors.verticalCenter: label9.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 10
    property alias color: invertThemeCheckBox.color
    property alias invertThemeCheckBox: invertThemeCheckBox
    activeFocusOnTab: true
    Accessible.name: qsTr("Invert theme")
    
    Keys.onSpacePressed: invertThemeCheckBox.checked = ! invertThemeCheckBox.checked
    Keys.onEnterPressed: invertThemeCheckBox.checked = ! invertThemeCheckBox.checked
    Keys.onReturnPressed: invertThemeCheckBox.checked = ! invertThemeCheckBox.checked
    
    Rectangle {
        id: invertThemeCheckBox
        anchors.fill: parent
        color: bgColor
        border.color: invertThemeFocusScope.activeFocus ? lightColor : "light gray"
        border.width: invertThemeFocusScope.activeFocus ? 2 : 1
        property bool checked: parameters.invertTheme
        Text {
            text: invertThemeCheckBox.checked ? qsTr("On") : qsTr("Off")
            anchors.centerIn: parent
            font.pointSize: 16
            color: fontColor
        }
        
        MouseArea {
            anchors.fill: parent
            onPressed: {
                invertThemeCheckBox.checked = ! invertThemeCheckBox.checked
            }
        }
        onCheckedChanged: {
            window.stopAudio()
            parameters.invertTheme = checked
            controlsRect.invertTheme = checked
            audioSettingsTab.invertTheme = checked
            graphSettingsTab.invertTheme = checked
            window.setColor()
        }
    }
}
