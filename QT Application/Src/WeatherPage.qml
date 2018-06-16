import QtQuick 2.0
import QtQuick 2.9
import QtQuick.Controls 2.2
//TODO: fix sp and dp for scalling
Page{
    id: today

    property int temperature: myNetwork.temperature
    property string temperature_color: "#FF5E3A"

    property int humidity: myNetwork.humidity
    property string humidity_color: "#1AD6FD"

    property int currentIndex: 0
    onCurrentIndexChanged: {
        if(currentIndex == 0)
            mainText.text = temperature.toFixed(0)+" C"
        else
            mainText.text = humidity.toFixed(0)+" %"

    }

//    property var alldata: [
//      { temperature: 12, description: qsTr("Foggy") },
//      { temperature: 32, description: qsTr("Sunny") }
//    ]

    // Background
    Rectangle {

        width: today.width
        height: today.height


      gradient: Gradient {
        GradientStop {
          position: 0
          color: today.currentIndex == 0 ? today.temperature_color : today.humidity_color

          Behavior on color { ColorAnimation { duration: 1500 } }
        }
        GradientStop {
          position: 1
          color: today.currentIndex == 0 ? today.temperature_color : today.humidity_color

          Behavior on color { ColorAnimation { duration: 1000 } }
        }
      }
    }

    Timer {
      interval: 3000
      repeat: true
      running: true
      onTriggered: {
          //console.log("timer ... "+main.currentIndex)

        if (today.currentIndex == 0)
          today.currentIndex = 1
        else
          today.currentIndex = 0
      }
    }

    // Top content
    Column {
      anchors.horizontalCenter: parent.horizontalCenter
      y: 10//dp(10)
      spacing: 10//dp(10)

      // Current time
      Text {
        id: timeLabel

        font.pixelSize: 22//sp(14)
        anchors.horizontalCenter: parent.horizontalCenter

        Timer {
          running: true
          interval: 1000 * 30
          triggeredOnStart: true
          repeat: true
          onTriggered: {
            timeLabel.text = new Date().toLocaleTimeString(Qt.locale(), Locale.ShortFormat)
          }
        }
      }

      // City
      Text {
        text: "Oran, DZ"
        font.pixelSize: 14//sp(22)
        anchors.horizontalCenter: parent.horizontalCenter
      }

    }

    // Centered content
    Column {
      id: col
      anchors.centerIn: parent

      // Main text
      Text {
        id: mainText

        property int temperature: today.temperature

        Component.onCompleted: text = temperature

        font.pixelSize: 140//sp(140)
        anchors.horizontalCenter: parent.horizontalCenter

//        onTemperatureChanged: {
//          var currentTemp = parseInt(tempText.text)
//          textTimer.restart()
//        }

//        Timer {
//          id: textTimer
//          interval: 40

//          onTriggered: {
//            // Check if we have to change the text
//            var currentTemp = parseInt(tempText.text)

//            if (tempText.temperature > currentTemp) {
//              tempText.text = ++currentTemp
//              restart()
//            }
//            else if (tempText.temperature < currentTemp) {
//              tempText.text = --currentTemp
//              restart()
//            }
//          }
//        }
      }

      // Description
//      Text {
//        id: descText
//        text: today.description
//        font.pixelSize: sp(28)
//        anchors.horizontalCenter: parent.horizontalCenter

//        Behavior on text {
//          SequentialAnimation {
//            NumberAnimation { target: descText; property: "opacity"; to: 0 }
//            PropertyAction { }
//            NumberAnimation { target: descText; property: "opacity"; to: 1 }
//          }
//        }
//      }

    }





}
