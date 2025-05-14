import QtQuick
import QtQuick.Timeline 1.0

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.height
    
    color: Constants.backgroundColor
    
    Image {
        id: speedometer
        x: 320
        y: 140
        width: 440
        height: 440
        source: "qrc:/qtquickplugin/images/template_image.png"
        sourceSize.height: 440
        sourceSize.width: 440
        fillMode: Image.PreserveAspectFit
    }
    
    Image {
        id: rpm
        x: 1160
        y: 140
        width: 440
        height: 440
        source: "qrc:/qtquickplugin/images/template_image.png"
        sourceSize.height: 440
        sourceSize.width: 440
        fillMode: Image.PreserveAspectFit
    }
    
    Rectangle {
        id: rectangle3
        x: 861
        y: 175
        width: 200
        height: 285
        color: "#ffffff"
    }
    
    Image {
        id: cooldesign
        x: 861
        y: 175
        width: 200
        height: 285
        source: "qrc:/qtquickplugin/images/template_image.png"
        sourceSize.height: 285
        fillMode: Image.PreserveAspectFit
    }
    
    Image {
        id: gearselect
        x: 780
        y: 466
        width: 180
        height: 180
        source: "qrc:/qtquickplugin/images/template_image.png"
        sourceSize.height: 180
        sourceSize.width: 180
        fillMode: Image.PreserveAspectFit
    }
    
    Image {
        id: fuelamount
        x: 960
        y: 466
        width: 180
        height: 180
        source: "qrc:/qtquickplugin/images/template_image.png"
        sourceSize.height: 180
        sourceSize.width: 180
        fillMode: Image.PreserveAspectFit
    }
    
    Rectangle {
        id: rectangle4
        x: 894
        y: 34
        width: 133
        height: 100
        color: "#ffffff"
    }
    
    Image {
        id: clock
        x: 894
        y: 34
        width: 133
        height: 100
        source: "qrc:/qtquickplugin/images/template_image.png"
        sourceSize.height: 100
        sourceSize.width: 133
        fillMode: Image.PreserveAspectFit
    }
    
    Image {
        id: turnindicator1
        x: 766
        y: 65
        width: 100
        height: 100
        source: "qrc:/qtquickplugin/images/template_image.png"
        sourceSize.height: 100
        sourceSize.width: 100
        fillMode: Image.PreserveAspectFit
    }
    
    Image {
        id: turnindicator2
        x: 1054
        y: 65
        width: 100
        height: 100
        source: "qrc:/qtquickplugin/images/template_image.png"
        sourceSize.height: 100
        sourceSize.width: 100
        fillMode: Image.PreserveAspectFit
    }
    
    Rectangle {
        id: rectangle1
        x: 0
        y: 355
        width: 215
        height: 365
        color: "#ffffff"
    }
    
    Image {
        id: iconindicators
        x: 0
        y: 355
        width: 215
        height: 365
        source: "qrc:/qtquickplugin/images/template_image.png"
        sourceSize.height: 365
        sourceSize.width: 215
        fillMode: Image.PreserveAspectFit
    }
    
    Rectangle {
        id: rectangle2
        x: 1705
        y: 355
        width: 215
        height: 365
        color: "#ffffff"
    }
    
    Image {
        id: coolantenginetemp
        x: 1705
        y: 355
        width: 215
        height: 365
        source: "qrc:/qtquickplugin/images/template_image.png"
        sourceSize.height: 365
        sourceSize.width: 215
        fillMode: Image.PreserveAspectFit
    }
    
    Image {
        id: coolshape1
        x: 28
        y: 65
        width: 160
        height: 150
        source: "qrc:/qtquickplugin/images/template_image.png"
        sourceSize.height: 150
        sourceSize.width: 160
        fillMode: Image.PreserveAspectFit
    }
    
    Image {
        id: coolshape2
        x: 1733
        y: 65
        width: 160
        height: 150
        source: "qrc:/qtquickplugin/images/template_image.png"
        sourceSize.height: 150
        sourceSize.width: 160
        fillMode: Image.PreserveAspectFit
    }
    
    Timeline {
        id: bootuptimeline
        animations: [
            TimelineAnimation {
                id: timelineAnimation
                running: true
                loops: 1
                duration: 1000
                to: 1000
                from: 0
            }
        ]
        startFrame: 0
        endFrame: 5000
        enabled: true
    }
    
    states: [
        State {
            name: "clicked"
        }
    ]
}
