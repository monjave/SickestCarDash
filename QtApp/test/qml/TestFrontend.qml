import QtQuick
import QtTest
import "CarDashboardContent"

TestCase {
    name: "Test Speed Integration"

    Screen01 {
        id: screen01
    }

    property alias speed: screen01.exposedSpeed

    function test_TestFunctionName() {
        compare(speed.opacity, 0, "Opacity: 0")
    }
}
