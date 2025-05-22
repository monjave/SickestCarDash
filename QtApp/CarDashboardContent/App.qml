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
    property int speedNumber: speedValue.speed
    property int rpmNumber: rpmValue.rpm

    DataSpeed {
        id: speedValue
    }

    function speedToAngle(speed) {
        const speedMin = 0;
        const speedMax = 180;
        const angleMin = 0;
        const angleMax = 270;

        const angle = angleMin + ((speed - speedMin) / (speedMax - speedMin)) * (angleMax - angleMin);

        return angle;
    }

    DataRPM {
        id: rpmValue
    }

    function rpmToAngle(rpm) {
        const rpmMin = 0;
        const rpmMax = 9000;
        const angleMin = 0;
        const angleMax = 270;

        const angle = angleMin + ((rpm - rpmMin) / (rpmMax - rpmMin)) * (angleMax - angleMin);

        return angle;
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

