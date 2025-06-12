

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import CarDashboard
import QtQuick.Timeline 1.0

Item {
    id: cluster
    width: Constants.width
    height: Constants.height

    property alias exposedSpeed: speedometer

    property alias exposedButton: playButton

    property alias gear: gearSelect

    property alias seatbelt: seatbeltIndicator
    property alias highlights: highLightsIndicator
    property alias abs: absIndicator
    property alias engineCheck: engineCheckIndicator
    property alias parking: parkingIndicator

    property alias turnLeft: turnIndicatorL
    property alias turnRight: turnIndicatorR

    property alias clockOne: clockOnes
    property alias clockTen: clockTens
    property alias clockHundred: clockHundreds
    property alias clockThousand: clockThousands

    Image {
        id: bgArt
        x: 0
        y: 0
        width: 1920
        height: 720
        source: "images/bgArtWIP.png"
        fillMode: Image.PreserveAspectFit

        Image {
            id: logoBg
            x: 0
            y: 0
            width: 1920
            height: 720
            opacity: 0
            source: "images/logoBg.png"
            fillMode: Image.PreserveAspectFit

            Image {
                id: logo
                x: 411
                y: 77
                width: 1099
                height: 567
                opacity: 0
                visible: true
                source: "images/logo.png"
                fillMode: Image.PreserveAspectFit
            }
        }

        Image {
            id: speedometer
            x: 200
            y: -3
            width: 725
            height: 725
            source: "dials/MPH210.png"
            mirror: false
            fillMode: Image.PreserveAspectFit

            Image {
                id: needleSpeed
                x: parent.width * 0.02702702702702702702702702702703
                y: parent.height * 0.02702702702702702702702702702703
                width: parent.width * 0.94594594594594594594594594594595
                height: parent.height * 0.94594594594594594594594594594595
                source: "pointers/NeedleBig.PNG"
                rotation: speedVar
                Behavior on rotation {
                    SpringAnimation {
                        spring: 1.3
                        damping: .15
                    }
                }

                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: speedNumbers
                x: 25
                y: 25
                width: 875
                height: 875
                visible: false
                source: "dialNumbers/mphNumbers.PNG"
                z: -1
                fillMode: Image.PreserveAspectFit
            }
        }

        Image {
            id: rpm
            x: 995
            y: -3
            width: 725
            height: 725
            source: "dials/DialBgBig.PNG"
            fillMode: Image.PreserveAspectFit

            Image {
                id: needleRPM
                x: parent.width * 0.02702702702702702702702702702703
                y: parent.height * 0.02702702702702702702702702702703
                width: parent.width * 0.94594594594594594594594594594595
                height: parent.height * 0.94594594594594594594594594594595
                source: "pointers/NeedleBig.PNG"
                rotation: rpmVar
                fillMode: Image.PreserveAspectFit
                Behavior on rotation {
                    SpringAnimation {
                        spring: 1.3
                        damping: .15
                    }
                }
            }

            Image {
                id: rpmNumbers
                x: 0
                y: 0
                width: parent.width
                height: parent.height
                source: "dialNumbers/rpmNumbers.PNG"
                z: -1
                fillMode: Image.PreserveAspectFit
            }
        }

        Image {
            id: gearSelect
            x: 885
            y: 285
            width: 150
            height: 150
            visible: true
            source: "images/N-center.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: fuel
            x: 1495
            y: 101
            width: 572
            height: 443
            visible: true
            source: "dials/DialBgSmall.PNG"
            fillMode: Image.PreserveAspectFit

            Image {
                id: fuelNeedle
                x: 0
                y: 0
                width: parent.width
                height: parent.height
                source: "pointers/NeedleSmall.PNG"
                rotation: fuelVar
                fillMode: Image.PreserveAspectFit
                Behavior on rotation {
                    SpringAnimation {
                        spring: 1.3
                        damping: .15
                    }
                }
            }

            Image {
                id: fuelNumbers
                x: 0
                y: 0
                width: parent.width
                height: parent.height
                source: "dialNumbers/fuelNumbers.PNG"
                z: -1
                fillMode: Image.PreserveAspectFit
            }
        }

        Image {
            id: clockColon
            x: 923
            y: 15
            width: 75
            height: 75
            visible: true
            source: "images/Colon.png"
            fillMode: Image.PreserveAspectFit

            Image {
                id: clockOnes
                x: 120
                y: 0
                width: 75
                height: 75
                source: "images/0.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: clockTens
                x: 50
                y: 0
                width: 75
                height: 75
                source: "images/0.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: clockHundreds
                x: -50
                y: 0
                width: 75
                height: 75
                source: "images/0.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: clockThousands
                x: -120
                y: 0
                width: 75
                height: 75
                source: "images/0.png"
                fillMode: Image.PreserveAspectFit
            }
        }

        Image {
            id: turnIndicatorL
            x: 797
            y: 40
            width: 225
            height: 225
            visible: false
            source: "images/LeftTurnSignal.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: turnIndicatorR
            x: 906
            y: 40
            width: 225
            height: 225
            visible: false
            source: "images/RightTurnSignal.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: playButtonGraphic
            x: 0
            y: 620
            width: 100
            height: 100
            source: "images/PausePlay.png"
            fillMode: Image.PreserveAspectFit
        }

        Button {
            id: playButton
            x: 0
            y: 620
            width: 100
            height: 100
            opacity: 0
            visible: true
            text: qsTr("")
            hoverEnabled: false
            icon.color: "#000000"
            display: AbstractButton.TextOnly
            icon.source: "images/PausePlay.png"
        }

        Image {
            id: seatbeltIndicator
            x: 65
            y: 8
            width: 150
            height: 150
            visible: false
            source: "images/Seatbelt.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: absIndicator
            x: 891
            y: 85
            width: 137
            height: 137
            visible: false
            source: "images/Abs.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: oilTemp
            x: -146
            y: 364
            width: 572
            height: 443
            visible: true
            source: "dials/DialBgSmall.PNG"
            fillMode: Image.PreserveAspectFit

            Image {
                id: oilTempNumbers
                x: 0
                y: 0
                width: parent.width
                height: parent.height
                source: "dialNumbers/oilTempNumbers.PNG"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: needleOilTemp
                x: 0
                y: 0
                width: parent.width
                height: parent.height
                source: "pointers/NeedleSmall.PNG"
                rotation: oilTempVar
                fillMode: Image.PreserveAspectFit
                Behavior on rotation {
                    SpringAnimation {
                        spring: 1.3
                        damping: .15
                    }
                }
            }
        }

        Image {
            id: coolantTemp
            x: -146
            y: 101
            width: 572
            height: 443
            opacity: 0
            visible: true
            source: "dials/DialBgSmall.PNG"
            fillMode: Image.PreserveAspectFit

            Image {
                id: coolantTempNumbers
                x: 0
                y: 0
                width: parent.width
                height: parent.height
                source: "dialNumbers/tempNumbers.PNG"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: needleCoolantTemp
                x: 0
                y: 0
                width: parent.width
                height: parent.height
                source: "pointers/NeedleSmall.PNG"
                rotation: coolantTempVar
                fillMode: Image.PreserveAspectFit
                Behavior on rotation {
                    SpringAnimation {
                        spring: 1.3
                        damping: .15
                    }
                }
            }
        }
        Image {
            id: highLightsIndicator
            x: 245
            y: 8
            width: 150
            height: 150
            visible: false
            source: "images/High_beams.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: parkingIndicator
            x: 1525
            y: 8
            width: 150
            height: 150
            visible: false
            source: "images/Parking_break.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: engineCheckIndicator
            x: 1706
            y: 8
            width: 150
            height: 150
            visible: false
            source: "images/Check_engine.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: voltage
            x: 1495
            y: 364
            width: 572
            height: 443
            source: "dials/DialBgSmall.PNG"
            fillMode: Image.PreserveAspectFit

            Image {
                id: voltageNumbers
                x: 0
                y: 0
                width: parent.width
                height: parent.height
                source: "dialNumbers/voltageNumbers.PNG"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: needleVoltage
                x: 0
                y: 0
                width: parent.width
                height: parent.height
                rotation: voltageVar
                source: "pointers/NeedleSmall.PNG"
                fillMode: Image.PreserveAspectFit
                Behavior on rotation {
                    SpringAnimation {
                        spring: 1.3
                        damping: .15
                    }
                }
            }
        }
    }

    Timeline {
        id: bootup
        animations: [
            TimelineAnimation {
                id: timelineAnimation
                running: true
                loops: 1
                duration: 3500
                to: 3500
                from: 0
            }
        ]
        startFrame: 2000
        endFrame: 3500
        enabled: true

        KeyframeGroup {
            target: logo
            property: "x"
            Keyframe {
                value: 411
                frame: 0
            }

            Keyframe {
                value: 411
                frame: 1000
            }

            Keyframe {
                value: 2500
                frame: 1500
            }
        }

        KeyframeGroup {
            target: logo
            property: "opacity"
            Keyframe {
                value: 1
                frame: 0
            }

            Keyframe {
                value: 1
                frame: 1500
            }

            Keyframe {
                value: 0
                frame: 1750
            }
        }

        KeyframeGroup {
            target: logoBg
            property: "opacity"
            Keyframe {
                value: 1
                frame: 0
            }

            Keyframe {
                value: 1
                frame: 1500
            }

            Keyframe {
                value: 0
                frame: 1751
            }
        }

        KeyframeGroup {
            target: speedometer
            property: "opacity"
            Keyframe {
                value: 0
                frame: 0
            }

            Keyframe {
                value: 0
                frame: 2000
            }

            Keyframe {
                value: 1
                frame: 3500
            }
        }

        KeyframeGroup {
            target: rpm
            property: "opacity"
            Keyframe {
                value: 0
                frame: 0
            }

            Keyframe {
                value: 0
                frame: 2000
            }

            Keyframe {
                value: 1
                frame: 3500
            }
        }

        KeyframeGroup {
            target: gearSelect
            property: "opacity"
            Keyframe {
                value: 0
                frame: 0
            }

            Keyframe {
                value: 0
                frame: 2000
            }

            Keyframe {
                value: 1
                frame: 3500
            }
        }

        KeyframeGroup {
            target: fuel
            property: "opacity"
            Keyframe {
                value: 0
                frame: 0
            }

            Keyframe {
                value: 0
                frame: 2000
            }

            Keyframe {
                value: 1
                frame: 3500
            }
        }

        KeyframeGroup {
            target: clockColon
            property: "opacity"
            Keyframe {
                value: 0
                frame: 0
            }

            Keyframe {
                value: 0
                frame: 2000
            }

            Keyframe {
                value: 1
                frame: 3500
            }
        }

        KeyframeGroup {
            target: turnIndicatorL
            property: "opacity"
            Keyframe {
                value: 0
                frame: 0
            }

            Keyframe {
                value: 0
                frame: 2000
            }

            Keyframe {
                value: 1
                frame: 3500
            }
        }

        KeyframeGroup {
            target: turnIndicatorR
            property: "opacity"
            Keyframe {
                value: 0
                frame: 0
            }

            Keyframe {
                value: 0
                frame: 2000
            }

            Keyframe {
                value: 1
                frame: 3500
            }
        }

        KeyframeGroup {
            target: seatbeltIndicator
            property: "opacity"
            Keyframe {
                value: 0
                frame: 0
            }

            Keyframe {
                value: 0
                frame: 2000
            }

            Keyframe {
                value: 1
                frame: 3500
            }
        }

        KeyframeGroup {
            target: oilTemp
            property: "opacity"
            Keyframe {
                value: 0
                frame: 0
            }

            Keyframe {
                value: 0
                frame: 2000
            }

            Keyframe {
                value: 1
                frame: 3500
            }
        }

        KeyframeGroup {
            target: coolantTemp
            property: "opacity"
            Keyframe {
                value: 0
                frame: 0
            }

            Keyframe {
                value: 0
                frame: 2000
            }

            Keyframe {
                value: 1
                frame: 3500
            }
        }

        KeyframeGroup {
            target: highLightsIndicator
            property: "opacity"
            Keyframe {
                value: 0
                frame: 0
            }

            Keyframe {
                value: 0
                frame: 2000
            }

            Keyframe {
                value: 1
                frame: 3500
            }
        }

        KeyframeGroup {
            target: absIndicator
            property: "opacity"
            Keyframe {
                value: 0
                frame: 0
            }

            Keyframe {
                value: 0
                frame: 2000
            }

            Keyframe {
                value: 1
                frame: 3500
            }
        }

        KeyframeGroup {
            target: engineCheckIndicator
            property: "opacity"
            Keyframe {
                value: 0
                frame: 0
            }

            Keyframe {
                value: 0
                frame: 2000
            }

            Keyframe {
                value: 1
                frame: 3500
            }
        }

        KeyframeGroup {
            target: parkingIndicator
            property: "opacity"
            Keyframe {
                value: 0
                frame: 0
            }

            Keyframe {
                value: 0
                frame: 2000
            }

            Keyframe {
                value: 1
                frame: 3500
            }
        }

        KeyframeGroup {
            target: playButtonGraphic
            property: "opacity"
            Keyframe {
                value: 1
                frame: 3500
            }

            Keyframe {
                value: 0
                frame: 0
            }

            Keyframe {
                value: 0
                frame: 2000
            }
        }

        KeyframeGroup {
            target: voltage
            property: "opacity"
            Keyframe {
                value: 1
                frame: 3500
            }

            Keyframe {
                value: 0
                frame: 0
            }

            Keyframe {
                value: 0
                frame: 2000
            }
        }
    }

    states: [
        State {
            name: "clicked"
        }
    ]
}
