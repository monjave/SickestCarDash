import QtQuick
import CarDashboard

Window {
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: "CarDashboard"

    visibility: Window.FullScreen

    property int speedVar: speedToAngle(carData.data.speed)
    property int rpmVar: rpmToAngle(carData.data.rpm)
    property int fuelVar: fuelToAngle(carData.data.fuel)
    property int voltageVar: voltageToAngle(carData.data.voltage)
    property int oilTempVar: oilTempToAngle(carData.data.oiltemp)
    property int coolantTempVar: coolantTempToAngle(carData.data.coolanttemp)

    property int gearShiftNumber: carData.data.gearshift

    property int seatbeltVar: carData.data.seatbelt
    property int highlightsVar: carData.data.highlights
    property int absVar: carData.data.abs
    property int enginecheckVar: carData.data.enginecheck
    property int parkingVar: carData.data.parking

    property int turnleftVar: carData.data.turnleft
    property int turnrightVar: carData.data.turnright

    property int speedNumber: carData.data.speed
    property int rpmNumber: carData.data.rpm
    property int fuelNumber: carData.data.fuel
    property int voltageNumber: carData.data.voltage
    property int oilTempNumber: carData.data.oiltemp
    property int coolantTempNumber: carData.data.coolanttemp

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

    function voltageToAngle(voltage) {
        const voltageMin = 9;
        const voltageMax = 19;
        const angleMin = 0;
        const angleMax = 80;

        const angle = angleMin + ((voltage - voltageMin) / (voltageMax - voltageMin)) * (angleMax - angleMin);

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

    function coolantTempToAngle(coolantTemp) {
        const coolantTempMin = 100;
        const coolantTempMax = 260;
        const angleMin = 0;
        const angleMax = 80;

        const angle = angleMin + ((coolantTemp - coolantTempMin) / (coolantTempMax - coolantTempMin)) * (angleMax - angleMin);

        return angle;
    }

    function gearShift() {

        switch (gearShiftNumber) {

        case 1:
            mainScreen.gear.source = "images/N-center.png"
            break;

        case 2:
            mainScreen.gear.source = "images/R-center.png"
            break;

        case 3:
            mainScreen.gear.source = "images/P-center.png"
            break;

        case 4:
            mainScreen.gear.source = "images/D-center.png"
            break;

        case 5:
            mainScreen.gear.source = "images/1.png"
            break;

        case 6:
            mainScreen.gear.source = "images/2.png"
            break;

        case 7:
            mainScreen.gear.source = "images/3.png"
            break;

        }

    }

    function clock() {
        mainScreen.clockThousand.source = "images/" + Math.floor(time / 60 / 10) + ".png"
        mainScreen.clockHundred.source = "images/" + Math.floor(time / 60 % 10) + ".png"
        mainScreen.clockTen.source = "images/" + Math.floor((time % 60) / 10) + ".png"
        mainScreen.clockOne.source = "images/" + Math.floor((time % 60) % 10) + ".png"
    }

    function seatbelt() {
        seatbeltVar ? mainScreen.seatbelt.visible = true : mainScreen.seatbelt.visible = false;
    }

    function highlights() {
        highlightsVar ? mainScreen.highlights.visible = true : mainScreen.highlights.visible = false;
    }

    function abs() {
        absVar ? mainScreen.abs.visible = true : mainScreen.abs.visible = false;
    }

    function enginecheck() {
        enginecheckVar ? mainScreen.enginecheck.visible = true : mainScreen.enginecheck.visible = false;
    }

    function parking() {
        parkingVar ? mainScreen.parking.visible = true : mainScreen.parking.visible = false;
    }

    function turnleft() {
        turnleftVar ? mainScreen.turnLeft.visible = true : mainScreen.turnLeft.visible = false;
    }

    function turnright() {
        turnrightVar ? mainScreen.turnRight.visible = true : mainScreen.turnRight.visible = false;
    }

    Screen01 {
        id: mainScreen 
    }


    /*Component.onCompleted: {
        mainScreen.exposedButton.clicked.connect(function() {
            carData.togglePaused()
        })
    }*/

    onGearShiftNumberChanged: {
        gearShift()
    }

    onTimeChanged: {
        clock()
    }

    onSeatbeltVarChanged: {
        seatbelt()
    }

    onHighlightsVarChanged: {
        highlights()
    }

    onAbsVarChanged: {
        abs()
    }

    onEnginecheckVarChanged: {
        enginecheck()
    }

    onParkingVarChanged: {
        parking()
    }

    onTurnleftVarChanged: {
        turnleft()
    }

    onTurnrightVarChanged: {
        turnright()
    }

}

