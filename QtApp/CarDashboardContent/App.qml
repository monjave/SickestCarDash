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

}

