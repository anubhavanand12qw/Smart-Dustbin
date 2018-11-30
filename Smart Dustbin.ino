 #include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);

const int trigPin = 5;
const int echoPin = 6;
long duration;
float distance;
const int led = 13;
int count=0;
void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  delay(100);
}
 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+91XXXXXXXXXX\"\r"); // Replace x with mobile number
  delay(1000);
  //String link = "http://www.google.com/maps/place/" + String(latitude) + "," + String(longitude) ;
  String link = "Your Dustbin number 1 is full, \nPlease click on the link below to get location \nlink: http://www.google.com/maps/place/" + String(28.4499646) + "," + String(77.58432010000001) ;
  mySerial.println(link);// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  count=count+1;
}
 void RecieveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(5000);
 }
 void CheckBinStatus()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = 0.034*(duration/2);
  Serial.println(distance);
  if (distance < 5)
  {
    //digitalWrite(led,HIGH);
    SendMessage();
    delay(1000);
    count=count+1;
  }
  else 
  {
    //digitalWrite(led,LOW);
  }
  delay(1500);
 }
void loop()
{
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
      SendMessage();
      break;
    case 'r':
      RecieveMessage();
      break;
  }

 if (mySerial.available()>0){
  char m=mySerial.read();
  Serial.write(m);
  if (m=='d'){
    m='p';
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
    duration = pulseIn(echoPin, HIGH);
    distance = 0.034*(duration/2);
    //Serial.println(distance);
    if (distance < 10)
    {
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      delay(1000);  // Delay of 1000 milli seconds or 1 second
      mySerial.println("AT+CMGS=\"+91XXXXXXXXXX\"\r"); // Replace x with mobile number
      delay(1000);
      //String link = "http://www.google.com/maps/place/" + String(latitude) + "," + String(longitude) ;
      //String link = "Your Dustbin number 1 is full, \nPlease click on the link below to get location \nlink: http://www.google.com/maps/place/" + String(28.4499646) + "," + String(77.58432010000001) ;
      mySerial.println("The status of your dustbin number 1 is HIGH");// The SMS text you want to send
      delay(100);
       mySerial.println((char)26);// ASCII code of CTRL+Z
      delay(1000);
    }
    else 
    {
      m='p';
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      delay(1000);  // Delay of 1000 milli seconds or 1 second
      mySerial.println("AT+CMGS=\"+91XXXXXXXXXX\"\r"); // Replace x with mobile number
      delay(1000);
      //String link = "http://www.google.com/maps/place/" + String(latitude) + "," + String(longitude) ;
      //String link = "Your Dustbin number 1 is full, \nPlease click on the link below to get location \nlink: http://www.google.com/maps/place/" + String(28.4499646) + "," + String(77.58432010000001) ;
      mySerial.println("The status of your dustbin number 1 is LOW");// The SMS text you want to send
      delay(100);
       mySerial.println((char)26);// ASCII code of CTRL+Z
      delay(1000);
    }
  }
  if(m=='a'){
    m='p';
    mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
    delay(1000);  // Delay of 1000 milli seconds or 1 second
    mySerial.println("AT+CMGS=\"+91XXXXXXXXXX\"\r"); // Replace x with mobile number
    delay(1000);
    //String link = "http://www.google.com/maps/place/" + String(latitude) + "," + String(longitude) ;
    //String link = "Your Dustbin number 1 is full, \nPlease click on the link below to get location \nlink: http://www.google.com/maps/place/" + String(28.4499646) + "," + String(77.58432010000001) ;
    mySerial.println("YOUR DUSTBIN NUMBER 1 IS CURRENTLY ACTIVE");// The SMS text you want to send
    delay(100);
     mySerial.println((char)26);// ASCII code of CTRL+Z
    delay(1000);
  }
 }
 else{
  if(count<1)
    CheckBinStatus();
 }
}
