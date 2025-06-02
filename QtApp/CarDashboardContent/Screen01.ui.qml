

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

    property alias exposedButton: playButton

    property alias gear: gearSelect

    property alias seatbelt: seatbeltIndicator
    property alias abs: absIndicator
    property alias highlights: highLightsIndicator
    property alias engineCheck: engineCheckIndicator
    property alias parking: parkingIndicator

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
            x: -27
            y: -70
            width: 925
            height: 925
            source: "dials/DialBgBig.PNG"
            mirror: false
            fillMode: Image.PreserveAspectFit

            Image {
                id: needleSpeed
                x: 25
                y: 25
                width: 875
                height: 875
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
                source: "dialNumbers/mphNumbers.PNG"
                z: -1
                fillMode: Image.PreserveAspectFit
            }
        }

        Image {
            id: rpm
            x: 1023
            y: -70
            width: 925
            height: 925
            source: "dials/DialBgBig.PNG"
            fillMode: Image.PreserveAspectFit

            Image {
                id: needleRPM
                x: 25
                y: 25
                width: 875
                height: 875
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
                x: 25
                y: 25
                width: 875
                height: 875
                source: "dialNumbers/rpmNumbers.PNG"
                z: -1
                fillMode: Image.PreserveAspectFit
            }
        }

        Image {
            id: gearSelect
            x: 885
            y: 318
            width: 150
            height: 150
            visible: true
            source: "images/P-center.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: fuelAmount
            x: 893
            y: 460
            width: 381
            height: 381
            visible: false
            source: "dials/DialBgSmall.PNG"
            fillMode: Image.PreserveAspectFit

            Image {
                id: fuelNeedle
                x: 0
                y: 0
                width: 381
                height: 381
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
                width: 381
                height: 381
                source: "dialNumbers/fuelNumbers.PNG"
                z: -1
                fillMode: Image.PreserveAspectFit
            }
        }

        Image {
            id: clockColon
            x: 923
            y: 96
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
            x: 641
            y: -92
            width: 320
            height: 320
            visible: false
            source: "images/LeftTurnSignal.png"
            mirror: false
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: turnIndicatorR
            x: 967
            y: -92
            width: 320
            height: 320
            visible: false
            source: "images/RightTurnSignal.png"
            fillMode: Image.PreserveAspectFit
        }

        Button {
            id: playButton
            x: 1820
            y: 680
            text: qsTr("Play/Pause")
        }

        Image {
            id: seatbeltIndicator
            x: 0
            y: 514
            width: 100
            height: 100
            visible: false
            source: "images/Seatbelt.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: absIndicator
            x: 825
            y: 439
            width: 250
            height: 250
            visible: true
            source: "images/Abs.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: oilTemp
            x: 1610
            y: 355
            width: 385
            height: 298
            visible: false
            source: "dials/DialBgSmall.PNG"
            fillMode: Image.PreserveAspectFit

            Image {
                id: oilTempNumbers
                x: 0
                y: 0
                width: 385
                height: 298
                source: "dialNumbers/oilTempNumbers.PNG"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: needleOilTemp
                x: 0
                y: 0
                width: 385
                height: 298
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
            id: coolShapeL
            x: 0
            y: 0
            width: 235
            height: 265
            source: "qrc:/qtquickplugin/images/template_image.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: coolShapeR
            x: 1685
            y: 0
            width: 235
            height: 260
            source: "qrc:/qtquickplugin/images/template_image.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: temp
            x: 1426
            y: 502
            width: 385
            height: 298
            opacity: 0
            visible: false
            source: "dials/DialBgSmall.PNG"
            fillMode: Image.PreserveAspectFit

            Image {
                id: tempNumbers
                x: 0
                y: 0
                width: 385
                height: 298
                source: "dialNumbers/tempNumbers.PNG"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: needleTemp
                x: 0
                y: 0
                width: 385
                height: 298
                source: "pointers/NeedleSmall.PNG"
                rotation: tempVar
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
            x: 108
            y: 514
            width: 100
            height: 100
            visible: false
            source: "images/High_beams.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: parkingIndicator
            x: 214
            y: 620
            width: 100
            height: 100
            visible: false
            source: "images/Parking_break.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: engineCheckIndicator
            x: 108
            y: 620
            width: 100
            height: 100
            visible: false
            source: "images/Check_engine.png"
            fillMode: Image.PreserveAspectFit
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
        startFrame: 0
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
            target: fuelAmount
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
            target: coolShapeL
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
            target: coolShapeR
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
            target: temp
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
    }

    states: [
        State {
            name: "clicked"
        }
    ]
}

/*##^##
Designer {
    D{i:0}D{i:42;invisible:true}D{i:43;invisible:true}
}
##^##*/

