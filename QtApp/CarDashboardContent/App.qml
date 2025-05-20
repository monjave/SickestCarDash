import QtQuick
import CarDashboard
import CircularBuffer.Data

Window {
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: "CarDashboard"

    //visibility: Window.FullScreen

    property int speedVar: speedToAngle(speedValue.speed)
    property int rpmVar: rpmToAngle(rpmValue.rpm)
    property int fuelVar: fuelToAngle(fuelValue.fuel)
    property int tempVar: tempToAngle(tempValue.temp)
    property int oilTempVar: oilTempToAngle(oilTempValue.oiltemp)

    property bool seatbeltBool: speedValue.seatbelt
    property bool highlightsBool: speedValue.highlights
    property bool absBool: speedValue.abs
    property bool enginecheckBool: speedValue.enginecheck
    property bool parkingBool: speedValue.parking

    property int speedNumber: speedValue.speed
    property int rpmNumber: rpmValue.rpm
    property int fuelNumber: fuelValue.fuel
    property int tempNumber: tempValue.temp
    property int oilTempNumber: oilTempValue.oiltemp
    property int gearShiftNumber: gearShiftValue.gearshift

    property int time: clockValue.clock
    property int minutes: 0
    property int hours: 0

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

