

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
            x: 320
            y: 140
            width: 440
            height: 440
            source: "dials/DialBgBig.PNG"
            mirror: false
            fillMode: Image.PreserveAspectFit

            Image {
                id: needleSpeed
                x: 20
                y: 20
                width: 400
                height: 400
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
                x: 20
                y: 20
                width: 400
                height: 400
                source: "dialNumbers/mphNumbers.PNG"
                z: -1
                fillMode: Image.PreserveAspectFit
            }

            Text {
                id: speedNum
                x: 208
                y: 304
                width: 24
                height: 21
                visible: false
                color: "#ffffff"
                text: speedNumber
                font.pixelSize: 28
                font.styleName: "Bold"
                font.family: "Times New Roman"
            }
        }

        Image {
            id: rpm
            x: 1160
            y: 140
            width: 440
            height: 440
            source: "dials/DialBgBig.PNG"
            fillMode: Image.PreserveAspectFit

            Image {
                id: needleRPM
                x: 20
                y: 20
                width: 400
                height: 400
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
                x: 20
                y: 20
                width: 400
                height: 400
                source: "dialNumbers/rpmNumbers.PNG"
                z: -1
                fillMode: Image.PreserveAspectFit
            }

            Text {
                id: rpmNum
                x: 190
                y: 284
                visible: false
                color: "#ffffff"
                text: rpmNumber
                font.pixelSize: 28
                font.family: "Times New Roman"
                font.styleName: "Bold"
            }
        }

        Image {
            id: centerDesign
            x: 860
            y: 218
            width: 200
            height: 255
            source: "qrc:/qtquickplugin/images/template_image.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: gearSelect
            x: 766
            y: 483
            width: 180
            height: 180
            source: "dials/DialBgSmall.PNG"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: fuelAmount
            x: 893
            y: 460
            width: 381
            height: 381
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
            id: clock
            x: 894
            y: 34
            width: 133
            height: 100
            source: "qrc:/qtquickplugin/images/template_image.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: turnIndicatorL
            x: 646
            y: 0
            width: 300
            height: 300
            source: "images/LeftTurnSignal.png"
            mirror: false
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: turnIndicatorR
            x: 974
            y: 0
            width: 300
            height: 300
            source: "images/RightTurnSignal.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: iconIndicators
            x: 0
            y: 355
            width: 235
            height: 365
            source: "qrc:/qtquickplugin/images/template_image.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: oilTemp
            x: 1610
            y: 355
            width: 385
            height: 298
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
            target: centerDesign
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
            target: clock
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
            target: iconIndicators
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
    }

    states: [
        State {
            name: "clicked"
        }
    ]
}
