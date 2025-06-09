import QtQuick
import CarDashboard

Window {
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: "CarDashboard"

    //visibility: Window.FullScreen

    property int speedVar: speedToAngle(carData.data.speed * 2.23694)
    property int rpmVar: rpmToAngle(carData.data.rpm)
    property int fuelVar: fuelToAngle(carData.data.fuel)
    property int tempVar: tempToAngle(carData.data.temp)
    property int oilTempVar: oilTempToAngle(carData.data.oiltemp)

    property int gearShiftNumber: carData.data.gearshift

    property int seatbeltVar: carData.data.seatbelt
    property int highlightsVar: carData.data.highlights
    property int absVar: carData.data.abs
    property int enginecheckVar: carData.data.enginecheck
    property int parkingVar: carData.data.parking

    property int speedNumber: carData.data.speed
    property int rpmNumber: carData.data.rpm
    property int fuelNumber: carData.data.fuel
    property int tempNumber: carData.data.temp
    property int oilTempNumber: carData.data.oiltemp

    property int time: carData.data.clock

    function speedToAngle(speed) {
        const speedMin = 0;
        const speedMax = 210;
        const angleMin = 0;
        const angleMax = 280;

        const angle = angleMin + ((speed - speedMin) / (speedMax - speedMin)) * (angleMax - angleMin);

        return angle;
    }

    function rpmToAngle(rpm) {
        const rpmMin = 0;
        const rpmMax = 7000;
        const angleMin = 0;
        const angleMax = 280;

        const angle = angleMin + ((rpm - rpmMin) / (rpmMax - rpmMin)) * (angleMax - angleMin);

        return angle;
    }

    function fuelToAngle(fuel) {
        const fuelMin = 0;
        const fuelMax = 100;
        const angleMin = 0;
        const angleMax = 80;

        const angle = angleMin + ((fuel - fuelMin) / (fuelMax - fuelMin)) * (angleMax - angleMin);

        return angle;
    }

    function tempToAngle(temp) {
        const tempMin = 100;
        const tempMax = 260;
        const angleMin = 0;
        const angleMax = 80;

        const angle = angleMin + ((temp - tempMin) / (tempMax - tempMin)) * (angleMax - angleMin);

        return angle;
    }

    function oilTempToAngle(oilTemp) {
        const oilTempMin = 0;
        const oilTempMax = 80;
        const angleMin = 0;
        const angleMax = 80;

        const angle = angleMin + ((oilTemp - oilTempMin) / (oilTempMax - oilTempMin)) * (angleMax - angleMin);

        return angle;
    }

    function gearShift() {
        mainScreen.gear.visible = true

        switch (gearShiftNumber) {

        /*case 1:
            mainScreen.gear.source = "images/P-center.png"
            break;

        case 2:
            mainScreen.gear.source = "images/R-center.png"
            break; */

        case 0:
            mainScreen.gear.source = "images/N-center.png"
            break;

        case 1:
            mainScreen.gear.source = "images/1.png"
            break;

        case 2:
            mainScreen.gear.source = "images/2.png"
            break;

        case 3:
            mainScreen.gear.source = "images/3.png"
            break;

        case 4:
            mainScreen.gear.source = "images/4.png"
            break;

        case 5:
            mainScreen.gear.source = "images/5.png"
            break;

        case 6:
            mainScreen.gear.source = "images/6.png"
            break;

        default: mainScreen.gear.visible = false
        }

    }

    function clock() {
        mainScreen.clockThousand.source = "images/" + Math.floor(time / 60 / 10) + ".png"
        mainScreen.clockHundred.source = "images/" + Math.floor(time / 60 % 10) + ".png"
        mainScreen.clockTen.source = "images/" + Math.floor((time % 60) / 10) + ".png"
        mainScreen.clockOne.source = "images/" + Math.floor((time % 60) % 10) + ".png"
    }

    function abs() {

        switch (absVar) {
        case 1:
            mainScreen.abs.visible = true;
            break;

        default:
            mainScreen.abs.visible = false;
        }
    }

    Screen01 {
        id: mainScreen 
    }


    Component.onCompleted: {
        mainScreen.exposedButton.clicked.connect(function() {
            carData.togglePaused()
        })
    }

    onGearShiftNumberChanged: {
        gearShift()
    }

    onTimeChanged: {
        clock()
    }

    onAbsVarChanged: {
        abs()
    }

}

