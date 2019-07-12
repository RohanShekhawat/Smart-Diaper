#define BLYNK_PRINT Serial                          //  For Serial printing the connection status and IP Adress
#include<BlynkSimpleEsp8266.h>                      //  Adding Library for Blynk and WiFi
#include<ESP8266WiFi.h> 

int x=0;
int y;                                              //  Defining Variable for iterator and to store value
int i=0;
char auth[]="ae9da73e507240ad83395238c8d41fe5";     //  Authentivcation code for Blynk app
char ssid[]="iBHubs";       
char pass[]="ibhubsguest";                          //  Storing the network name and password in variable
BlynkTimer timer;                                   //  Creating object timer of class BlynkTimer
void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);                           //  Starting the serial monitor and setting up the baud rate
    Blynk.begin(auth,ssid,pass);                    //  Here Octabrix connects to blynk cloud 
    pinMode(A0,INPUT);                              //  Defining the pin for recieving data
    timer.setInterval(1000L,myTimerEvent);          //  setting time interval of sending consecutive data
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run() ;                                     //  to process incoming request and do the housekeeping of blynk connected
  timer.run();
   
     
}
void myTimerEvent()                                 //  Function for sending data and Triggering Notifications
{
  i++;
  y=analogRead(A0);                                 //  Recieving the data from sensor
  Serial.print(" Y IS : ");
  Serial.println(y);                                //  printing data on serial monitor
  x=x+y;
  if(i==5)                                          //  Taking average of 5 reading consecutive raeding
  {
    x=x/5;
  Blynk.virtualWrite(V5,(980-x));                   //  Sending the data to blynk cloud
  Serial.print("average is : ");
  Serial.println(x);
  if(x>560&&x<650)                                  // Sending Email notification at certain values of humidity
  {
    Blynk.notify("Diaper is a little wet");
    Blynk.email("iec2017054@iiita.ac.in","Baby Update","Diaper is a little wet");
   }
 if(x>450&&x<540)
  {
    Blynk.notify("Baby is feeling uncomfortable,its time to change");
    Blynk.email("iec2017054@iiita.ac.in","Baby Update","Baby is feeling uncomfortable,its time to change");
  }
 if(x<370)
 {
  Blynk.notify("Hurry CHANGE THE DIAPER!!! Baby might get Rashes");
  Blynk.email("iec2017054@iiita.ac.in","Baby Update","Hurry CHANGE THE DIAPER!!! Baby might get Rashes");
  }
  i=0;
  x=0;
  }
 
}

