#include <Arduino.h>

int ser_get[] = {0,0,0};



byte CRC8(const byte *data, size_t length) {
  uint8_t crc = 0x00;
  while (length--) {
    crc ^= *data++;
    for (uint8_t i = 0; i < 8; i++) {
      crc = (crc << 1) ^ ((crc & 0x80) ? 0x07 : 0);
    }
  }
  return crc;
}

// void get_serial(){
//     static uint8_t buffer[7];
//   static size_t index = 0;
  
//   while (Serial.available() > 0) {
//     buffer[index++] = Serial.read();
    
//     if (index >= 7) {
        
      
//       if (CRC8(buffer, 6) == buffer[6]) {

//         //Serial.write(0x06);  // Отправляем ACK

//         for(int i = 0; i < 3; i++){
//         ser_get[i] = (buffer[2*i+1] << 8) | buffer[2*i];}       
       
//       } else {
//         //Serial.write(0x15); // Отправляем NAK
//       }
      
//       index = 0; // Сброс для следующего пакета
//     }
//   }

// }

char test_g[8];
byte test_b[8];
// void get_from_cam()
// {  
//   if (Serial.available()>0){

//     memset(test_g,0,strlen(test_g));
//     while(Serial.available()>0){int bytesRead = Serial.readBytesUntil('\n', test_g, 10);} 
//     Serial.print(test_g);
//     memcpy(test_b, test_g, 8);
//     if (strlen(test_g) >= 5){
//         for(int i = 0; i < 3; i++){
//             ser_get[i] = (test_b[2*i+1] << 8) | test_b[2*i];}   
//     }

//     // leds.on(1,0, (atoi(get))/600, 0);
// }

// //   for(short i = 0; i <20; i++){
// //     output[i]='\0';
// //   }
  
// }
