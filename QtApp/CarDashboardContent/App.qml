import QtQuick
import CarDashboard
import CircularBuffer.Data

Window {
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: "CarDashboard"

    DataSpeed {
        id: speedValue
    }

    DataRPM {
        id: rpmValue
    }

    Screen01 {
        id: mainScreen 
    }


    /*Text {
        id: speedDisplay
        text: "Massive text"
        font.pixelSize: speedValue.speed
        x: 1000
        y: 300
        z: 10
        color: "#ffffff"
    }*/


}

