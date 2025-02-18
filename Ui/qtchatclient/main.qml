import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Chat Client App")

    Connections {
        target: client
        onNewMessage: {
            listModelMessages.append({ message: ba + "" })
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        RowLayout {
            TextField {
                id: textFieldIP
                placeholderText: qsTr("Server IP")
                Layout.fillWidth: true
                onAccepted: buttonConnect.clicked()
            }
            TextField {
                id: textFieldPort
                placeholderText: qsTr("Server Port")
                Layout.fillWidth: true
                onAccepted: buttonConnect.clicked()
            }
            Button {
                id: buttonConnect
                text: qsTr("Connect")
                onClicked: client.connectToServer(textFieldIP.text, textFieldPort.text)
            }
            Button {
                id: buttonDisconnect
                text: qsTr("Disconnect")
                visible: client.isConnected()
                onClicked: client.disconnectFromServer()
            }
        }

        ListView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            clip: true
            model: ListModel {
                id: listModelMessages
                ListElement { message: qsTr("Welcome to the Chat Client!") }
            }
            delegate: ItemDelegate {
                text: message
                background: Rectangle {
                    color: index % 2 ? "#f0f0f0" : "#e0e0e0"
                    radius: 5
                }
            }
            ScrollBar.vertical: ScrollBar {}
        }

        RowLayout {
            TextField {
                id: textFieldMessage
                placeholderText: qsTr("Your Message...")
                Layout.fillWidth: true
                onAccepted: buttonSend.clicked()
            }
            Button {
                id: buttonSend
                text: qsTr("Send")
                onClicked: {
                    if (!textFieldMessage.text.trimmed().isEmpty()) {
                        client.sendMessage(textFieldMessage.text)
                        textFieldMessage.clear()
                    }
                }
            }
        }
    }
}
