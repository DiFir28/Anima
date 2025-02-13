#include "setup/config.h"
#include "movement/movement.h"

Motor motor1(0,10);

void setup() {
  canInit();
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  attachInterrupt(0,stop, FALLING);
  attachInterrupt(1,play, RISING);
  

  
}

void loop() {
  if(act){
    for(int i=0;i<4;i++){
      if (i ==break_m)continue;
      motor[i].go(0.4);
  }
}
delay(10);
}



// struct can_frame frame;

// int encode = 0;
// uint16_t encoderOffset = 12345;

// uint32_t _speed = 600; 
// int _time = 600;

// int sign(int a){
//   return 2*(a>0)-2;
//   }
// void setup() {
//   Serial.begin(115200);

//   canInit();
// }
// void loop() { 
// if (k == 0){
//   frame.can_id = motor_id[i]; k =1;}
  
//     frame.can_dlc = 8;
//     uint32_t speedcontrol = 10000 ;


//         // frame.data[0] = 0xA2;
//         // frame.data[1] = 0x00;
//         // frame.data[2] = 0x00;
//         // frame.data[3] = 0x00;
//         // frame.data[4] = *(uint8_t*)(&speedcontrol);
//         // frame.data[5] = *((uint8_t*)(&speedcontrol) + 1);
//         // frame.data[6] = *((uint8_t*)(&speedcontrol) + 2);
//         // frame.data[7] = *((uint8_t*)(&speedcontrol) + 3);

//    can.sendMessage(&frame);  //передаем CAN сообщение
//   delayMicroseconds(100);
//   Serial.println();
// }
