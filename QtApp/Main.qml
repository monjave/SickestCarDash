import QtQuick
import QtQuick.Controls
import QtQuick.Timeline 1.0

Window {
    id: window
    width: 1920
    height: 720
    visible: true

Item {
    id: cluster
    //width: Constants.width
    //height: Constants.height
    visible: true

    Image {
        id: bgArt
        x: 0
        y: 0
        width: 1920
        height: 720
        source: "assets/images/bgArt.png"
        sourceSize.height: 720
        sourceSize.width: 1920
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: logoBg
        x: 0
        y: 0
        width: 1920
        height: 720
        opacity: 0
        source: "assets/dials/DialBg.png"
        z: 5
        sourceSize.height: 720
        sourceSize.width: 1920
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: speedometer
        x: 320 - width / 2
        y: 140
        width: 440
        height: 440
        opacity: 1
        source: "assets/dials/DialBg.png"
        transformOrigin: Item.Center
        sourceSize.height: 440
        sourceSize.width: 440
        fillMode: Image.PreserveAspectFit

        Image {
            id: needle1
            x: 20
            y: 20
            width: 400
            height: 400
            source: "assets/pointers/Needle.png"
            transformOrigin: Item.Center
            sourceSize.height: 400
            sourceSize.width: 400
            fillMode: Image.PreserveAspectFit
        }
    }

    Image {
        id: rpm
        x: 1160 - width / 2
        y: 140
        width: 440
        height: 440
        opacity: 0
        source: "assets/dials/DialBg.png"
        transformOrigin: Item.Center
        sourceSize.height: 440
        sourceSize.width: 440
        fillMode: Image.PreserveAspectFit

        Image {
            id: needle2
            x: 20
            y: 20
            width: 400
            height: 400
            source: "assets/pointers/Needle.png"
            transformOrigin: Item.Center
            sourceSize.height: 400
            sourceSize.width: 400
            fillMode: Image.PreserveAspectFit
        }
    }

    Image {
        id: cooldesign
        x: 861 - width / 2
        y: 175
        width: 200
        height: 285
        transformOrigin: Item.Center
        source: "assets/dials/DialBg.png"
        sourceSize.height: 285
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: gearselect
        x: 780 - width / 2
        y: 466
        width: 180
        height: 180
        opacity: 1
        transformOrigin: Item.Center
        source: "assets/dials/DialBg.png"
        sourceSize.height: 180
        sourceSize.width: 180
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: fuelamount
        x: 960 - width / 2
        y: 466
        width: 180
        height: 180
        transformOrigin: Item.Center
        source: "assets/dials/DialBg.png"
        sourceSize.height: 180
        sourceSize.width: 180
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: clock
        x: 894 - width / 2
        y: 34
        width: 133
        height: 100
        transformOrigin: Item.Center
        source: "assets/dials/DialBg.png"
        sourceSize.height: 100
        sourceSize.width: 133
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: turnindicator1
        x: 766 - width / 2
        y: 65
        width: 100
        height: 100
        transformOrigin: Item.Center
        source: "assets/dials/DialBg.png"
        sourceSize.height: 100
        sourceSize.width: 100
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: turnindicator2
        x: 1054 - width / 2
        y: 65
        width: 100
        height: 100
        transformOrigin: Item.Center
        source: "assets/dials/DialBg.png"
        sourceSize.height: 100
        sourceSize.width: 100
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: iconindicators
        x: 0 - width / 2
        y: 355
        width: 215
        height: 365
        transformOrigin: Item.Center
        source: "assets/dials/DialBg.png"
        sourceSize.height: 365
        sourceSize.width: 215
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: coolantenginetemp
        x: 1705 - width / 2
        y: 355
        width: 215
        height: 365
        transformOrigin: Item.Center
        source: "assets/dials/DialBg.png"
        sourceSize.height: 365
        sourceSize.width: 215
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: coolshape1
        x: 28 - width / 2
        y: 65
        width: 160
        height: 150
        opacity: 1
        transformOrigin: Item.Center
        source: "assets/dials/DialBg.png"
        sourceSize.height: 150
        sourceSize.width: 160
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: coolshape2
        x: 1733 - width / 2
        y: 65
        width: 160
        height: 150
        transformOrigin: Item.Center
        source: "assets/dials/DialBg.png"
        sourceSize.height: 150
        sourceSize.width: 160
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: logo
        x: 760 - width / 2
        y: 160
        width: 400
        height: 400
        opacity: 0
        source: "assets/images/Hotwheel.png"
        z: 5
        sourceSize.height: 400
        sourceSize.width: 400
        transformOrigin: Item.Center
        fillMode: Image.PreserveAspectFit
    }

    Timeline {
        id: bootup
        animations: [
            TimelineAnimation {
                id: timelineAnimation
                running: true
                loops: 1
                duration: 5000
                to: 5000
                from: 0
            }
        ]
        startFrame: 0
        endFrame: 5000
        enabled: true

        KeyframeGroup {
            target: speedometer
            property: "opacity"
            Keyframe {
                value: 0
                frame: 2000
            }

            Keyframe {
                value: 1
                frame: 3500
            }

            Keyframe {
                value: 0
                frame: 0
            }
        }

        KeyframeGroup {
            target: logo
            property: "opacity"
            Keyframe {
                value: 1
                frame: 1952
            }

            Keyframe {
                value: 1
                frame: 0
            }

            Keyframe {
                value: 0
                frame: 2022
            }
        }

        KeyframeGroup {
            target: logo
            property: "x"
            Keyframe {
                value: 560
                frame: 998
            }

            Keyframe {
                value: 2000
                frame: 1500
            }
        }

        KeyframeGroup {
            target: rpm
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
            target: gearselect
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
            target: fuelamount
            property: "opacity"
            Keyframe {
                value: 0
                frame: 0
            }

            Keyframe {
                value: 1
                frame: 3500
            }

            Keyframe {
                value: 0
                frame: 2000
            }
        }

        KeyframeGroup {
            target: coolantenginetemp
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
            target: coolshape2
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
            target: turnindicator2
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
            target: clock
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
            target: turnindicator1
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
            target: cooldesign
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
            target: iconindicators
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
            target: coolshape1
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

}
