import QtQuick
import CarDashboard
import CircularBuffer.Speed

Window {
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: "CarDashboard"

    DataSpeed {
        id: speedValue
    }

    Screen01 {
        id: mainScreen 
    }

    /*
    Text {
        id: speedDisplay
        text: parseInt(speedValue)
        font: 50
        x: 1000
        y: 300
        z: 10
        color: "#ffffff"
    }
    */

}

