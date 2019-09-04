#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include<SoftwareSerial.h>

SoftwareSerial s(3,1);

const char* host = "ecell.in";

float voltage=220.0, current=20.0, phase=2.0, power=30.0;
char a[50];
String voltage_s="", current_s="",phase_s="", power_s="", data="";
int i=0;
void setup()
{
//  Serial.begin(115200);
  Serial.begin(9600);
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

//  GET();
}

void loop() {

    
    delay(500);
    
Serial.println("Checking... ");
    if (Serial.available()>0)
    { 
      while (Serial.available()>0)
    {
        a[i] = char(Serial.read());
        Serial.print(a[i]) ; 
        i++;  
      } 
      i=0;

      Serial.println(a);
      data = (String)a;
      
      String voltage_s = getValue(data, ':', 0);
      String current_s = getValue(data, ':', 1);
      String phase_s = getValue(data, ':', 2);
      String power_s = getValue(data, ':', 3);

      voltage = voltage_s.toFloat();
      current = current_s.toFloat();
      phase = phase_s.toFloat();
      power = power_s.toFloat();
      
      Serial.print("voltage:");
      Serial.println(voltage);
      Serial.print("current:");
      Serial.println(current);
      Serial.print("phase:");
      Serial.println(phase);
      Serial.print("power:");
      Serial.println(power);

      GET();

  }
     
      
  }

  // If you only need to post data to the database then you don't need the code below:
void GET(void)
{
//  float voltage=220.0, current=20.0, phase=2.0, power=30.0;
  HTTPClient http;    //Declare object of class HTTPClient
 
  

  Serial.print("connecting to ");
  Serial.println(host);
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  else {
    Serial.println("connection success");
    }
//String url = "/edl/edl.php";
String url = "/v1/api/user/userlist";

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(10);

  // Read all the lines of the reply from server and print them to Serial
  Serial.println("Respond:");
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();

  Serial.print("Sending data : Voltage =  ");
    Serial.print(voltage);
    Serial.print(", Current =  ");
    Serial.print(current);
    Serial.print(", Phase =  ");
    Serial.print(phase);
    Serial.print(", Power =  ");
    Serial.println(power);

    Serial.print("Sending....");
    
  String get_data = "?voltage="+String(voltage)+"&current="+String(current)+"&phase="+String(phase)+"&power="+String(power);
  String Link = "http://edl.ecell.in/store_data.php"+get_data;  //Requeste webpage
  
  Serial.println(Link);
  http.begin(Link);     //Specify request destination
 
  int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload
 
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
 
  http.end();  //Close connection
//  voltage+=2;
//  current+=1.5;
//  power+=20.0;
//  phase+=0.2;
  
  delay(5000);  //GET Data at every 5 seconds

}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
