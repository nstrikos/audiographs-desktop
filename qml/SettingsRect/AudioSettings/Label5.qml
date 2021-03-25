import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

Label {
    id: label5
    text: qsTr("Explore mode") + ":"
    anchors.top: label4.bottom
    anchors.topMargin: 30
    anchors.left: parent.left
    anchors.leftMargin: 10
    width: 80
    height: 15
    color: fontColor
}
