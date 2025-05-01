import QtQuick 2.15
import QtQuick.Controls 2.15
//import "JSONListModel/JSONListModel.qml"

Item {
    id: jsonLoader
    property bool isVisible: false

    function loadJson(filePath) {
        var xhr = new XMLHttpRequest();
        xhr.open("GET", filePath);
        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                if (xhr.status === 200) {
                    var jsonObject = JSON.parse(xhr.responseText);
                    isVisible = jsonObject.isVisible;
                } else {
                    console.error("Failed to load JSON file");
                }
            }
        }
        xhr.send();
    }
}
