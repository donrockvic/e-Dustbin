#define IP  "api.thingspeak.com" // thingspeak.com
String GET = "GET http://api.thingspeak.com/update?key=JO89O8COMII4FJAS&field1=";
int trigPin = 11;    //Trig - green Jumper
int echoPin = 12;    //Echo - yellow Jumper
long duration;
int d;
void setup()
{
 pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
  Serial.println("AT");
  delay(2000);
  if (Serial.find("OK")) {
    Serial.println("Got response");
    Serial.println("AT+CWMODE=1");
    delay(2000);
    Serial.println("AT+CWJAP=\"ATUL\",\"#tagatul\"");
    delay(3000);
    if (Serial.find("OK")) {
      Serial.println("WiFi connected");
    }
  }
}
void loop()
{

 // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // convert the time into a distance
  d = (duration/2) / 29.1;
 
  Serial.print(d);
  Serial.println();
  
  delay(250);
Serial.println(d);
  
 
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",80";
  Serial.println(cmd);
  delay(2000);
  if (Serial.find("Error")) {
    Serial.print("found Errr");
    return;
  }
  String distance = String(d);
  cmd = GET + distance + "\r\n\r\n";

  Serial.print("AT+CIPSEND=");
  Serial.println(cmd.length());
  
  if (Serial.find(">")) {
    Serial.println(cmd);
    Serial.println("forwarded to cloud");
  } else {
    Serial.println("AT+CIPCLOSE");
  }
  Serial.println("request sent...");
  delay(5000);
}
