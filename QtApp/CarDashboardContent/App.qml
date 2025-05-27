import QtQuick
import CarDashboard
import CircularBuffer.Data

Window {
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: "CarDashboard"

    property int speedVar: speedToAngle(speedValue.speed)
    property int rpmVar: rpmToAngle(rpmValue.rpm)
    property int fuelVar: fuelToAngle(fuelValue.fuel)
    property int tempVar: tempToAngle(tempValue.temp)
    property int oilTempVar: oilTempToAngle(oilTempValue.oiltemp)

    property int speedNumber: speedValue.speed
    property int rpmNumber: rpmValue.rpm
    property int fuelNumber: fuelValue.fuel
    property int tempNumber: tempValue.temp
    property int oilTempNumber: oilTempValue.oiltemp

    DataSpeed {
        id: speedValue
    }

    DataRPM {
        id: rpmValue
    }

    DataFuel {
        id: fuelValue
    }

    DataTemp {
        id: tempValue
    }

    DataOilTemp {
        id: oilTempValue
    }

    function speedToAngle(speed) {
        const speedMin = 0;
        //const speedMax = 180;
        const speedMax = 140;
        const angleMin = 0;
        const angleMax = 280;

        const angle = angleMin + ((speed - speedMin) / (speedMax - speedMin)) * (angleMax - angleMin);

        return angle;
    }

    function rpmToAngle(rpm) {
        const rpmMin = 0;
        //const rpmMax = 9000;
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

    Screen01 {
        id: mainScreen 
    }

    Component.onCompleted: {
        mainScreen.exposedButton.clicked.connect(function() {
            speedValue.togglePaused()
            rpmValue.togglePaused()
            fuelValue.togglePaused()
            tempValue.togglePaused()
            oilTempValue.togglePaused()
        })
    }
}

