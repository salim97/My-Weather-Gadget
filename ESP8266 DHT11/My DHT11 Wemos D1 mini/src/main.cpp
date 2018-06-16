#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <IPAddress.h>
#include <WiFiUDP.h>
#include <DHT.h>


/*---------------------------------*/
// DHT11 temperature  & tHumidity
/*--------------------------------*/
DHT dht;
#define pin_data_DHT D7

/*---------------*/
// wifi config
/*----------------*/
char* ssid = "r2";
char* password = "qt2016c++";

/*---------------*/
// UDP packet handler
/*----------------*/
IPAddress ipBroadCast;
unsigned int udpPort=8236; // port output data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
WiFiUDP udp;

//methods....
void myUdpSend(String msg);
void checkRecieved();


float g_humidity, g_temperature ;

void setup() {
    // put your setup code here, to run once:
    //start connecting to wifi....
    WiFi.begin(ssid,password);

    //start serial interface for debuging...
    Serial.begin(115200);

    // wait untill esp8266 connected to wifi...
    while(WiFi.status()!=WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    // debuging ...
    Serial.println("");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP()); // todo: config ip broadcast

    ipBroadCast = WiFi.localIP() ;
    ipBroadCast[3] = 255;
     pinMode(LED_BUILTIN, OUTPUT);



     dht.setup(pin_data_DHT); // data pin 2
     // set udp port for listen...
     udp.begin(udpPort);
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
                                  // but actually the LED is on; this is because
                                  // it is acive low on the ESP-01)
delay(1000);                      // Wait for a second
digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
delay(1000);

delay(dht.getMinimumSamplingPeriod());

 g_humidity = dht.getHumidity();
 g_temperature = dht.getTemperature();
 myUdpSend("<temperature>"+String(g_temperature));
 myUdpSend("<humidity>"+String(g_humidity));
 //check err code, you must send only correcct value
 //myUdpSend("<dht11_status>"+String(dht.getStatusString()));

checkRecieved();

}


void myUdpSend(String msg)
{
    // convert string to char array
    int UDP_PACKET_SIZE = msg.length();
    char udpBuffer[UDP_PACKET_SIZE] ;
    msg.toCharArray(udpBuffer, UDP_PACKET_SIZE) ;
    Serial.println("send: "+msg);

    // send msg broadcast to port destinie
    udp.beginPacket(ipBroadCast, udpPort);
    udp.write(udpBuffer, sizeof(udpBuffer));
    udp.endPacket();
}
void checkRecieved()
{
    int packetSize = udp.parsePacket();

    if(packetSize)
    {
        Serial.println("");
        Serial.print("Received packet of size ");
        Serial.println(packetSize);
        Serial.print("From ");
        IPAddress remote = udp.remoteIP();
        for (int i =0; i < 4; i++)
        {
            Serial.print(remote[i], DEC);
            if (i < 3)
            {
                Serial.print(".");
            }
        }
        Serial.print(", port ");
        Serial.println(udp.remotePort());

        // read the packet into packetBufffer
        udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);

        Serial.println("Contents:");
        for (int i =0; i < packetSize; i++)
            Serial.print(packetBuffer[i]);

        // //traitment of packet
        // String myString = String(packetBuffer);
        // if(myString.indexOf("<servo>") >= 0)
        // {
        //     myString.replace("<servo>","");
        //     int valueI = myString.toInt();
        //     Serial.println("valueI "+String(valueI));
        //     if(valueI >= 0 && valueI <= 360 )
        //      servo.write(valueI);   // turn the LED on (HIGH is the voltage level)
        //     else
        //       myUdpSend("<ERREUR>valueI "+String(valueI));
        //
        //     myUdpSend("</servo>"+myString);
        // }
        // for (int i =0; i < packetSize; i++)
        //     packetBuffer[i]= 0;
        // myString = "";

    }
}
