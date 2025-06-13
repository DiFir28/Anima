#pragma once
#include "setup/config.h"


void gyro_init(){ 
    GY_Serial.begin(115200);  
    delay(3000);            
    GY_Serial.write(0xA5);
    GY_Serial.write(0x54);
    delay(1000);   
    GY_Serial.write(0xA5);
    GY_Serial.write(0x55);
    delay(100);    
    GY_Serial.write(0xA5);
    GY_Serial.write(0x53);
    delay(100);  

}

float gyro_read(){
    static int raw;
    static unsigned char counter = 0;
    static char buffer[50];
    char tmp;  // Variabel temporary
  while (GY_Serial.available()) {
    tmp = GY_Serial.read();
    buffer[counter++] = tmp;
    if (tmp == '\n') {                                    // Langkah 1
      buffer[counter] = 0;                      // Karakter terminator
      raw = atof(strtok(buffer + 5, ","));  // Langkah 2-4
      counter = 0;
    }
  }
  return raw*DEG_TO_RAD;
}