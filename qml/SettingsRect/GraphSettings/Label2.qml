import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

Label {
    id: label2
    text: qsTr("Background color") + ":"
    anchors.top: label1.bottom
    anchors.left: parent.left
    anchors.leftMargin: 10
    anchors.topMargin: 30
    width: 80
    height: 15
    color: fontColor
}
