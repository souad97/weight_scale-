#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
//#include<SoftwareSerial.h>
const int rs = A4, en = A3, d4 = A2, d5 = A1, d6 = A0, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
//equation lineaire val= -0.0250+0.0043*P;
#include "HX711.h"
#define DOUT  5
#define CLK  6
HX711 scale(DOUT, CLK);
//const byte txpin=1;
//const byte rxpin=0;
//SoftwareSerial myserial(rxpin,txpin);
float val;
float calibration_factor = 48000; //-7050 worked for my 440lb max scale setupvoid setup() 
void setup ()
{
Serial.begin(9600);
pinMode(7,OUTPUT);
digitalWrite(7,HIGH);// 5v hx711
//myserial.begin(9600);
lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 
pinMode(11,OUTPUT);
pinMode(12,OUTPUT);
digitalWrite(12,HIGH);
pinMode(7,OUTPUT);
digitalWrite(7,HIGH);

  

 /*Serial.println("HX711 calibration sketch");
 Serial.println("Remove all weight from scale");
 Serial.println("After readings begin, place known weight on scale");
 Serial.println("Press + or a to increase calibration factor");
 Serial.println("Press - or z to decrease calibration factor");*/
  val=0;
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  long zero_factor = scale.read_average(); //Get a baseline reading
  //Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  //Serial.println(zero_factor);
  lcd.print("PROJET BALANCE");
  delay(5000);
  lcd.setCursor(0,1);
  lcd.println(val);
}
void loop() {
  //scale.tare(); 
   scale.set_scale(calibration_factor); //Adjust to this calibration factor
    val=scale.get_units();
   //Serial.println(val);
   //delay(00);
   val=(val+0.0250)/0.0043;
   //Serial.println(val);
    if(val>100)
  {
    digitalWrite(11,1);
    lcd.println("votre poids est :");
   //Serial.println("votre poids est :");
    //myserial.println(val);
    delay(1000);
    lcd.setCursor(0,1);
    lcd.println(val);
    Serial.print(val);
    //Serial.println(val);
    lcd.setCursor(8,1);
    lcd.println("gramme");
    //Serial.println("gramme");
    delay(8000);
    lcd.clear();
    lcd.print("RESET");
    val=val-val;
    //Serial.println("RESET");
    delay(8000);
     scale.tare();
     lcd.clear();
     digitalWrite(11,0);
   }
   else
   {lcd.print("ATTENTE DE POID");
   //Serial.println("ATTENRE DE POIDS");
    delay(500);
    lcd.clear();
    }
     val=val-val;
  
 }
