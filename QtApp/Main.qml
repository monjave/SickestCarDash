import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

Window {
    id: win
    visible: true
    width: 1920
    height: 720
    //visibility: "FullScreen"
    title: qsTr("Speed Dial Logic")
    color: "white";

    Rectangle {
        id: bg
        width: 1920
        height: 720
        color: "#1e1e1e"

        Image {
            id: speedometer
            //x: 850
            x: 630
            y: 250
            width: 220
            height: 220
            source: "assets/dials/DialBg.png"
            sourceSize.height: 440
            sourceSize.width: 440
            fillMode: Image.PreserveAspectFit


            Text {
                id: text1
                x: 42
                y: 165
                color: "#ffffff"
                text: qsTr("0")
                font.pixelSize: 12
                font.family: "Horizon"
                font.styleName: "Bold"
                /*
                Text {
                    visible: if (slider.value >= 0 && slider.value < 10) {
                                 setVisible: true
                             } else {
                                 setVisible: false
                             }

                    id: text1Glow
                    anchors.centerIn: parent
                    font.pixelSize: 18
                    color: "#E4080A"
                    text: qsTr("0")
                    font.family: "Horizon"
                    font.styleName: "Bold"
                    z: -1
                } */
            }

            Text {
                id: text2
                x: 22
                y: 130
                color: "#ffffff"
                text: qsTr("20")
                font.pixelSize: 12
                font.family: "Horizon"
                font.styleName: "Bold"
            }

            Text {
                id: text3
                x: 16
                y: 93
                color: "#ffffff"
                text: qsTr("40")
                font.pixelSize: 12
                font.family: "Horizon"
                font.styleName: "Bold"
            }

            Text {
                id: text4
                x: 28
                y: 58
                color: "#ffffff"
                text: qsTr("60")
                font.pixelSize: 12
                font.family: "Horizon"
                font.styleName: "Bold"
            }

            Text {
                id: text5
                x: 53
                y: 31
                color: "#ffffff"
                text: qsTr("80")
                font.pixelSize: 12
                font.family: "Horizon"
                font.styleName: "Bold"
            }

            Text {
                id: text6
                x: 83
                y: 15
                color: "#ffffff"
                text: qsTr("100")
                font.pixelSize: 12
                font.family: "Horizon"
                font.styleName: "Bold"
            }

            Text {
                id: text7
                x: 120
                y: 17
                color: "#ffffff"
                text: qsTr("120")
                font.pixelSize: 12
                font.family: "Horizon"
                font.styleName: "Bold"
            }

            Text {
                id: text8
                x: 157
                y: 36
                color: "#ffffff"
                text: qsTr("140")
                font.pixelSize: 12
                font.family: "Horizon"
                font.styleName: "Bold"
            }

            Text {
                id: text9
                x: 168
                y: 67
                color: "#ffffff"
                text: qsTr("160")
                font.pixelSize: 12
                font.family: "Horizon"
                font.styleName: "Bold"
            }

            Text {
                id: text11
                x: 69
                y: 190
                color: "#ffffff"
                text: qsTr("Odometer")
                font.pixelSize: 16
                font.family: "Horizon"
                font.styleName: "Bold"
            }

            Image {
                id: needle
                x: 110
                y: 108
                width: 104
                height: 4
                source: "assets/pointers/Needle.png"
                sourceSize.width: 218
                sourceSize.height: 10
                fillMode: Image.PreserveAspectFit

                transform: Rotation {
                    id: needleRotation
                    origin.x: 0
                    origin.y: 2
                    angle: slider.value + 135
                    Behavior on angle {
                        SpringAnimation {
                            spring: 1.3
                            damping: .15
                        }
                    }
                }
            }
        }

        Slider {
            id: slider
            x: 860
            y: 493
            from: 0
            to: 200
            value: 0
            width: 300
        }

        Text {
            id: text10
            x: 700
            y: 499
            color: "#ffffff"
            text: qsTr("Speed: " + parseInt(slider.value * 0.8) + " MPH")
            font.pixelSize: 20
            font.family: "Horizon"
            font.styleName: "Bold"
        }

        /*Rectangle {
            id: colorOverlay
            width: 1920
            height: 720
            color: "#5DE2E7"
            opacity: 0.2
        } */
    }
}
