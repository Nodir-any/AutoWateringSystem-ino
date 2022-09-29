/*
	Hydroleaders team project!! 
	Tursunqulov Avazbek - technical engineer
	Ashurov Nodir - assistant engineer, designer
	
	automated pot project, that can water the plant automatically and prints out information on the display; 
	NOTE: since general code has been worked on, project can be applied to even big Greenhouse facilities with minor adjustments.
*/






//LiquidCrystal_I2C LCD(0x27,16,2); // read LCD name on display
//
//void loop() {
//   LCD.noDisplay();
//   delay(500);
//   LCD.display();
//   delay(500);
//}

#include <SimpleDHT.h>
#include <LiquidCrystal_I2C.h> // open library for QAPASS 1602

LiquidCrystal_I2C lcd(0x27,16,2); // read LCD name on display
Int wetness=A0;
Int water=A1;
Int dht=A2;
Int pump=8;
Int mator=9;
Int pumpled=10;
Int matorled=16;

SimpleDHT11 dht11;

Const int air_wetness = 1023;   
Const int water_wetness = 322;
Int T_N_Q = 0;
Int T_N_F = 0;
Int waterlevel=0;
Void setup() {
Serial.begin(9600); 
  pinMode(wetness,INPUT);
  pinMode(water,INPUT);
  pinMode(dht,INPUT);
  pinMode(pump,OUTPUT);
  pinMode(mator,OUTPUT);
  pinMode(pumpled,OUTPUT);
  pinMode(matorled,OUTPUT);
  digitalWrite(water,1);
  lcd.init(); // turns on LCD display
  lcd.backlight(); // noBacklight activation
  lcd.setCursor(4, 0);
  lcd.print(“YOUR”);   
  lcd.setCursor(3, 1);
  lcd.print(“PROJECT”); 
  Serial.println(“    NAME”);
  Serial.println(“   HERE”);
  Delay(5000);
  Lcd.clear();
  
}
Void loop() {
  
  //temperature of room
 Byte temperature = 0;
 Byte a_wetness = 0;
 Int errors = SimpleDHTErrSuccess;
  If ((errors = dht11.read(dht, &temperature, &a_wetness, NULL)) != SimpleDHTErrSuccess) 
  {
    Serial.print(“DHT11 not found, errors=”); Serial.println(errors);
    
  }
  
  Serial.print(“ Temperature  “); Serial.print((int)temperature); Serial.print(“ °C, “); 
  Serial.print(“ Wetness  “); Serial.print((int)a_wetness); Serial.println(“ %”);

  Lcd.setCursor(0, 0);
  Lcd.print(“Temperature”);
  Lcd.setCursor(10, 0);
  Lcd.print((int)temperature); lcd.print(“ C”);
  
  Lcd.setCursor(0, 1);
  Lcd.print(“Wetness”);
  Lcd.setCursor(10, 1);
  Lcd.print((int)a_wetness);lcd.print(“ %”);

  If(temperature>=30)
{digitalWrite(mator,0);
digitalWrite(matorled,1);}
else if(temperature<=25){digitalWrite(mator,1);
digitalWrite(matorled,0);}

  delay(2000);
 lcd.clear();

 // soil wetness 
T_N_Q = analogRead(wetness);
Serial.println(T_N_Q);
T_N_F = map(T_N_Q, air_wetness, water_wetness, 0, 100); //wetness


  If(0<= T_N_F <= 100)
{
  Serial.print(T_N_F);
  Serial.println(“%”);
  Lcd.setCursor(1, 0);
  Lcd.print(“Soil wetness”);
  Lcd.setCursor(6, 1);
  Lcd.print(T_N_F);  
}
If(T_N_F >= 100)
{
  Lcd.setCursor(6, 1);
  Lcd.print(“100”);
}
Else if(T_N_F <=0)
{
  Lcd.setCursor(6, 1);
  Lcd.print(“0”);
}
  Lcd.print(“ %”);
  Delay(2000);
  Lcd.clear();

   If(T_N_F<=40 && digitalRead(water)==0){digitalWrite(pump,0); digitalWrite(pumpled,1);}
  Else if(T_N_F>=80 | digitalRead(water)==1){digitalWrite(pump,1); digitalWrite(pumpled,0);}

 
  Lcd.setCursor(4, 0);
  Lcd.print(“Water”);
  Serial.print(“Water”);
  If(digitalRead(water)==0){lcd.print(“ has”);Serial.println(“ has”);}
Else {lcd.print(“ nothave”);Serial.println(“ nothave”);}

  Lcd.setCursor(2, 1);
  Lcd.print(“Pump”);
  Serial.print(“Pump”);
  If(digitalRead(pump)==0){lcd.print(“ on”);Serial.println(“ on”);}
  Else {lcd.print(“ off”);Serial.println(“ off”);}
   Delay(2000);
  Lcd.clear();
 
}
