#pragma once
#include "setup/config.h"


void gyro_init(){ 
    Serial3.begin(115200);  
    delay(3000);            
    Serial3.write(0xA5);
    Serial3.write(0x54);
    delay(1000);   
    Serial3.write(0xA5);
    Serial3.write(0x55);
    delay(100);    
    Serial3.write(0xA5);
    Serial3.write(0x53);
    delay(100);  

}

float gyro_read(){
    static int raw;
    static unsigned char counter = 0;
    static char buffer[50];
    char tmp;  // Variabel temporary
  while (Serial3.available()) {
    tmp = Serial3.read();
    buffer[counter++] = tmp;
    if (tmp == '\n') {                                    // Langkah 1
      buffer[counter] = 0;                      // Karakter terminator
      raw = atof(strtok(buffer + 5, ","));  // Langkah 2-4
      counter = 0;
    }
  }
  return raw*DEG_TO_RAD;
}