import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

Window {
    visible: true
    width: 480
    height: 920
    title: qsTr("Hello World")

    //FontLoader { id: normalFont; source: "qrc:///Lato-Light.ttf" }
    //FontLoader { id: normalFont; source: "qrc:/Lato-Light.ttf" }


    WeatherPage{
         anchors.fill: parent
    }


}
