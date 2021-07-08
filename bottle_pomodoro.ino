//GND - GND
//VCC - VCC
//SDA - Pin A4
//SCL - Pin A5
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
const int mpuAddress = 0x68;  //Puede ser 0x68 o 0x69
MPU6050 mpu(mpuAddress);
int ax, ay, az;
int gx, gy, gz;

const unsigned long ONE_HOUR = 60UL * 60UL * 1000UL; 
//const int warningLed = 13;
unsigned long elapsedDrink ;
unsigned long lastDrink;

void printTab()
{
   Serial.print(F("\t"));
}
void printRAW()
{
   Serial.print(F("a[x y z] g[x y z]:t"));
   Serial.print(ax); printTab();
   Serial.print(ay); printTab();
   Serial.print(az); printTab();
   Serial.print(gx); printTab();
   Serial.print(gy); printTab();
   Serial.println(gz);
}
void setup()
{
  
   pinMode(LED_BUILTIN, OUTPUT);
   // pinMode(warningLed, OUTPUT);

   Serial.begin(9600);
   Wire.begin();
   mpu.initialize();
   Serial.println(mpu.testConnection() ? F("IMU iniciado correctamente") : F("Error al iniciar IMU"));
}
void loop()
{
   // Leer las aceleraciones y velocidades angulares
   mpu.getAcceleration(&ax, &ay, &az);
   mpu.getRotation(&gx, &gy, &gz);
  // printRAW();

   elapsedDrink = millis() - lastDrink;
   Serial.println(elapsedDrink);

   if (elapsedDrink > ONE_HOUR) {
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
   } else {
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
   }
   
   if (ax > 15000 || ax < -15000 || ay > -5000 ) {
      //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      Serial.print(ax); Serial.print("/");  Serial.print(ay);
      lastDrink = millis(); // drinking now 
      
   } else {
      //digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
   }
   
   delay(100);
}
