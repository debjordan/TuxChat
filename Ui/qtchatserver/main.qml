import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Server App")

    Connections {
        target: server
        onNewMessage: {
            listModelMessages.append({ message: ba + "" })
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        // Lista de Mensagens
        ListView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            clip: true
            model: ListModel {
                id: listModelMessages
                ListElement { message: "Server started on port 45000" }
            }
            delegate: ItemDelegate {
                text: message
            }
            ScrollBar.vertical: ScrollBar {}
        }

        // Campo de Mensagem e Botão de Envio
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
                        server.sendMessage(textFieldMessage.text)
                        textFieldMessage.clear()
                    }
                }
            }
        }
    }
}
