import QtQuick
import QtQuick.Controls

Window {
    width: 1920
    height: 720
    visible: true
    title: qsTr("Speedometer Proto")
    color: "grey"

    Image {
        id:speed
        source:"speedometerBackground.png"
        x: 150
        y: 300
        width: 200
        height: 200
        //fillMode: background.PreserveAspectFit
        Image {
            id:needle
            source:"needle.png"
            anchors.centerIn: parent
            width: 200
            height: 200
            rotation: 240

            transform: Rotation {
                id: rotation
                origin.x: needle.width / 2
                origin.y: needle.height / 2
                angle: 0
            }
        }
    }

    Image {
        id:fuel
        source:"speedometerBackground.png"
        x: 850
        y: 300
        width: 200
        height: 200
        //fillMode: background.PreserveAspectFit
        Image {
            id:needle2
            source:"needle.png"
            anchors.centerIn: parent
            width: 200
            height: 200
            rotation: 240

            transform: Rotation {
                id: rotation2
                origin.x: needle.width / 2
                origin.y: needle.height / 2
                angle: 0
            }
        }
    }

    Rectangle {
        id:oilTemp
        x: 600
        y: 400
        width: 100
        height: 50
        color: "red"
    }

    Rectangle {
        id:waterTemp
        x: 600
        y: 200
        width: 100
        height: 50
        color: "blue"
    }

    Button {
        id:button
        x: 60
        y: 400
        width:80
        height:50
        text:"Toggle Dials"

        onClicked: {
            //needle.rotation += 30
            //springAnimation.running = true
            speed.visible = !speed.visible
            fuel.visible = !fuel.visible
        }
    }

    SpringAnimation {
        id:springAnimation
        target: rotation
        property:"angle"
        from: 0
        to: 360
        duration: 200
        spring: 1.5
        damping: 0.3
    }

}
