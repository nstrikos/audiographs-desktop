import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

Label {
    id: label6
    text: qsTr("Use different notes\n for negative values") + ":"
    anchors.top: audioLabel5.bottom
    anchors.topMargin: 30
    anchors.left: parent.left
    anchors.leftMargin: 10
    width: 80
    height: 15
    color: fontColor
}
