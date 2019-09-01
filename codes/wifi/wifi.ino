
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include<SoftwareSerial.h>

SoftwareSerial s(3,1);

const int led1 = 1;
void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting");
  WiFi.begin("despair", "123456789");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(led1, OUTPUT);
  //GET();
}

void loop() {

  digitalWrite(led1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(led1, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);   
    
//    delay(5000);
//    GET();
    while (Serial.available()>0)
    {
        Serial.println(s.read()) ;  
      }  
  }

  // If you only need to post data to the database then you don't need the code below:
void GET(void)
{
  HTTPClient http;    //Declare object of class HTTPClient
 
  
String url = "http://2e6f19ee.ngrok.io/node/evm/vote/mumbai/BSP/";

Serial.print("Requesting URL: ");

  Serial.println();

//  String get_data = "?voltage="+String(voltage)+"&current="+String(current)+"&phase="+String(phase)+"&power="+String(power);
//  String Link = "http://edl.ecell.in/store_data.php"+get_data;  //Requeste webpage

  Serial.println(url);
  http.begin(url);     //Specify request destination
 
  int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload
 
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println("Response:");
  Serial.println(payload);    //Print request response payload
 
  http.end();  //Close connection

  
  delay(5000);  //GET Data at every 5 seconds

}
