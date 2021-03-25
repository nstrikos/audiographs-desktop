import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

Label {
    id: label2
    text: qsTr("Minimum frequency") + ":"
    anchors.top: label1.bottom
    anchors.left: parent.left
    anchors.topMargin: 30
    anchors.leftMargin: 10
    width: 80
    height: 15
    color: fontColor
}
