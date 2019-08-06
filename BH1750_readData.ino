/*
 *___BH1750 GY-302 Ambient Light Sensor___* 
 Connection:
 BH1750 -   
 ------------------
 VCC    -   3.3V or 5V
 GND    -   GND
 SCL    -   SCL(A5 on Arduino Nano, Uno, on esp8266 free selectable[generally Pin 1])
 SDA    -   SDA(A4 on Arduino Nano, Uno, on esp8266 free selectable[generally Pin 2])
 ADD    -   NC (or GND)
 */
 
#include <Wire.h>

byte BH1750_Device_Address = 0x23; // I2C address for BH1750 light sensor
unsigned int Lux_value = 0;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  delay(200);
}

void loop() {
  BH1750_Initialise();
  Lux_value = BH1750_Read();
  Serial.print(Lux_value);
  Serial.println(" [lx]");
//  float FtCd = Lux / 10.764;
//  float Wattsm2 = Lux / 683.0;
//  Serial.print(FtCd, 2);
//  Serial.println("[FC]");
//  Serial.print(Wattsm2, 4);
//  Serial.println("[Watts / m ^ 2]");
  delay(2000);
}

unsigned int BH1750_Read() {
  unsigned int value = 0;
  Wire.beginTransmission(BH1750_Device_Address);
  Wire.requestFrom(BH1750_Device_Address, 2);
  while (Wire.available()) {
    value <<= 8;
    value |= Wire.read();
  }
  Wire.endTransmission();
  return value / 1.2; // Convert to Lux
}

void BH1750_Initialise() {
  Wire.beginTransmission(BH1750_Device_Address);
  Wire.write(0x10); // set resolution to 1 Lux
  Wire.endTransmission();
  delay(200);
}
