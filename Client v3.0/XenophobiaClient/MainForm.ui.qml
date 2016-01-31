import QtQuick 2.4
import QtQuick.Window 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Rectangle {
    property alias serverTextField: server_ip_text
    width: 480
    height: 640

    GridView {
        id: connect_view
        anchors.fill: parent
        contentHeight: 640
        contentWidth: 480

        Image {
            source: "qrc:///main/background_main"
        }


        TextField {
            id: server_ip_text
            objectName: "server_ip_text"
            width: 480
            height: 47
            font.pointSize: 14
            placeholderText: "Enter server ip"

            anchors {
                left: parent.left
                top: parent.top
                leftMargin: 0
                topMargin: 560
            }

            style: TextFieldStyle {
                textColor: "black"
                background: Rectangle {
                    radius: 2
                    color: "white"
                    opacity: 0.5
                    implicitWidth: 480
                    implicitHeight: 34
                    border.color: "#004DFF"
                }
            }

            visible: true
            focus: true
            selectByMouse: true
            onAccepted: _gamewindow.LobbyInputAccepted()
        }

        Image {
            id: select_role_image
            width: 100
            height: 100
            visible: false
            opacity: 0
            source: "qrc:///main/border"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    available_roles_list.visible = !available_roles_list.visible;
                }
            }
        }

        ListView {
            id: available_roles_list
            objectName: "available_roles_list"
            width: parent.width
            height: parent.height * 0.5
            x: 0
            y: 160
            visible: false
            model: available_roles_model
            delegate: Image {
                source: "qrc:///roles/" + role

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        select_role_image.source = parent.source;
                    }
                }
            }
        }
    }
    states: [
        State {
            name: "register_state"

            PropertyChanges {
                target: server_ip_text
                text: ""
                width: 406
                height: 47
                placeholderText: "Enter character's name"
            }

            PropertyChanges {
                target: select_role_image
                x: 406
                y: 560
                width: 74
                height: 47
                visible: true
                anchors.leftMargin: -74
                anchors.topMargin: -80
                opacity: 1
            }
        }
    ]
}
