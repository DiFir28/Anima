// #include "setup/config.h"
// #include "setup/math.cpp"
// #include "movement/movement.h"
// #include "Sensors/Gyro/gyro.h"
// #include "Leds/leds.h"
// #include "Sensors/Line_circle/line.h"
// #include "Protocols/Serial.hpp"
// #include <Servo.h>

// //  line_circle circle;

// Leds leds(8, 33);
// Servo motorA;

// char output[20]="";

// int ret_i = 0;
//     short controlPin[3] = {22, 23, 24};
//     short slavPins[2] = {A0, A1};
//     struct lisens line_sensors[16];

// float ball_angle = 0.0;
// int ball_len =0;
// int getting = 0;
// float goals[] = {0.0, 0.0};
// bool have_ball = 0;

// // void setConfigurate(int conf)
// // {
// //     for (int conf_i = 2; conf_i > -1; conf_i--)
// //     {
// //         digitalWrite(controlPin[conf_i], (conf >= pow(2, conf_i)));
// //         conf = conf - pow(2, conf_i) * (conf >= pow(2, conf_i));
// //     }
// // }

// //char get[15] = "";

// int get_arr[] = {0,0,0,0, 0};
// float get_rbp[] = {0,0,0,0};
// const char* gett;

// size_t countChar(const char* str, char target) {
//   size_t count = 0;
//   for (size_t i = 0; str[i] != '\0'; i++) {
//       if (str[i] == target) {
//           count++;
//       }
//   }
//   return count;
// }

// void convert(int count){
//   if (countChar(gett, ',') != count+1){
//     return;
//   }
//   char* sep =strchr(gett, ',');
//   for(int i = 0; i<count; i++){
//     char* l_sep = sep;

//      sep = strchr(sep+1, ',');
//     char buf[7] = "";
//     strncpy(buf, l_sep+1, sep - l_sep-1);
//     get_arr[i] = atoi(buf );

//     }
//   }

// int drib_pow = 1450;

// unsigned long last_time = 0;
// void setup()
// {
//   canInit();
//   gyro_init();

//   motorA.attach(26);
//   motorA.writeMicroseconds(1900);
//   delay(2000);
//   motorA.writeMicroseconds(1000);
//   delay(2000);
//   motorA.writeMicroseconds(1400);
//   delay(2000);
//   motorA.writeMicroseconds(0);
//   delay(2000);

//   pinMode(LED_BUILTIN, OUTPUT);
//   attachInterrupt(0, stop, FALLING);
//  // attachInterrupt(1, play, RISING);
//   stop();

//   leds.on(0, 2, 2, 0);

//   pinMode(22,OUTPUT);
//   pinMode(23,OUTPUT);
//   pinMode(24,OUTPUT);

//   pinMode(A0, INPUT);
//   pinMode(A1, INPUT);

//   pinMode(4,INPUT);

//   RBP_Serial.begin(115200);
//   Serial.begin(115200);

//   leds.on(0, 0, 100, 100);
//   delay(1000);

// }

// bool play = 0;
// bool last_4 = 0;

// unsigned long drib_update = 0;

// float curl_ball_ang = 0.0;
// float move_ang = 0.0;
// float yaw_ang = 0.0;
// float move_speed = 4.0;

// int drib_flag = 1;

// float aang = 0.0;

// void loop()
// {

//   motorA.writeMicroseconds(1480 - get_arr[3]);
//   Serial.print(play);

//   // RBP_Serial.print("  ");

//   //get_from_cam();

//   //go(radvec(ball_angle, 0.4 * (abs(between(gyro_read(), ball_angle)) < 0.3)), between(0, ball_angle));
//   //go(radvec(2,1),1.0);

//    //go(radvec(between(0, ball_angle),    1.2 * (abs(between(gyro_read(), ball_angle)) < 0.8) ),  between(0, ball_angle));

//   if (play){
//     go( radvec(get_arr[0]/1000.0,get_arr[1]/1000.0 ), get_arr[2]/1000.0, get_arr[4]/1000.0);
//   }else{
//     go(radvec(0,0),0);
//   }
//   Serial.print("accept^");
//   Serial.print(" ");
//   Serial.print(get_arr[0]/1000.0);
//   Serial.print(" ");
//   Serial.print(get_arr[1]/1000.0);
//   Serial.print(" ");
//   Serial.print(get_arr[2]/1000.0);
//   Serial.print(" ");
//   Serial.print(1450 - get_arr[3]);
//   Serial.print(" ");

//   if (digitalRead(4) && !last_4){
//     play = !play;
//   }
//   last_4 = digitalRead(4);

//   RBP_Serial.print("   ");

//   Serial.print(gyro_read());
//   RBP_Serial.println( gyro_read() );

//   if (RBP_Serial.available() > 0) {
//     String received = RBP_Serial.readStringUntil('\n');
//     //received.trim();
//     Serial.print(" ");
//     Serial.print(received);
//     gett =  received.c_str();

//     convert(5);

//   }
//   Serial.println("");

//   for(int i =0; i<4;i++){
//     Serial.print(get_arr[i]);
//     Serial.print(" ");
//     }

//   // RBP_Serial.print(" ");
//   // // RBP_Serial.print(get);
//   // RBP_Serial.print(" ");
//   // RBP_Serial.print(drib_pow);
//   // RBP_Serial.print(" ");
//   // RBP_Serial.print(ball_len);
//   // RBP_Serial.println(" ");
//   delay(20);

// }


/*
#include <SPI.h>     //Library for using SPI Communication
#include <mcp2515.h> //Library for using CAN Communication
struct can_frame frame;
// MCP2515 can(10);
MCP2515 can(34);

int encode = 0;
uint16_t encoderOffset = 12345;

uint32_t _speed = 600;
int _time = 600;

int sign(int a)
{
  return 2 * (a > 0) - 2;
}

void encupdate()
{
  int enc = 0;
  if (can.readMessage(&frame) == MCP2515::ERROR_OK)
  {
    if (frame.data[0] == 0x9C)
    {
      Serial.print("C");
      Serial.print(frame.data[2] + (frame.data[3] << 8));
      Serial.print("S");
      Serial.print(frame.data[4] + (frame.data[5] << 8));
      Serial.print("E");
      Serial.println(frame.data[6] + (frame.data[7] << 8));
    }
  }
  else
  {
    // Serial.println("Nope");
  }
}
// uint32_t _speed = -1000;
// uint32_t speedcontrol = -100000;

int motor_id[] = {0x141, 0x142, 0x143, 0x144};

unsigned long Accel = 1000;
unsigned long tor = 40;

void setup()
{
  Serial.begin(115200);

  SPI.begin(); // инициализация связи по протоколу SPI

  can.reset();
  // can.setBitrate(CAN_1000KBPS, MCP_16MHZ);  //устанавливаем скорость шины CAN 500 кбит/с и частоту кварцевого генератора 8 МГц
  can.setBitrate(CAN_1000KBPS, MCP_8MHZ);
  can.setNormalMode();
  // can.reset();
  delay(100);
  pinMode(18, INPUT);
  attachInterrupt(5, encupdate, FALLING);
  //  frame.can_id = motor_id[1];
  //  frame.can_dlc = 8;
  //
  //  frame.data[0] = 0x32;
  //  frame.data[1] = 0x00;
  //  frame.data[2] = 5;
  //  frame.data[3] = 5;
  //  frame.data[4] = 5;
  //  frame.data[5] = 5;
  //  frame.data[6] = 5;
  //  frame.data[7] = 5;
  //  can.sendMessage(&frame);
  //  delay(1);

  //  frame.data[0] = 0x35;
  //  frame.data[1] = 0x00;
  //  frame.data[2] = 0x00;
  //  frame.data[3] = 0x00;
  //  frame.data[4] = *(uint8_t*)(&Accel);
  //  frame.data[5] = *((uint8_t*)(&Accel) + 1);
  //  frame.data[6] = *((uint8_t*)(&Accel) + 2);
  //  frame.data[7] = *((uint8_t*)(&Accel) + 3);
  //  can.sendMessage(&frame);
  //      if (can.readMessage(&frame) == MCP2515::ERROR_OK) {
  //      Serial.print("send");
  //      Serial.print(" ");
  //                  for (int ii=1; ii<8;ii++){
  ////                    Serial.print(ii);
  ////                    Serial.print(" ");
  //                  Serial.print(frame.data[ii]);
  //                  Serial.print(" ");}
  //}
  delay(1);

  //  frame.data[0] = 0x0;0
  //  frame.data[1] = 0x00;
  //  frame.data[2] = 0x00;
  //  frame.data[3] = 0x00;
  //  frame.data[4] = 0xA2;
  //  frame.data[5] = 0x00;
  //  frame.data[6] = 0x00;
  //  frame.data[7] = 0x00;
}
int last = 0;
unsigned long t = 0;
long enc;
long a[4];
long cur = 0;
void loop()
{
  //  frame.can_id = motor_id[0];
  //  frame.can_dlc = 8;
  //  frame.data[0] = 0x9C;
  //  frame.data[1] = 0;
  //  frame.data[2] = 0;
  //  frame.data[3] = 0;
  //  frame.data[4] = 0;
  //  frame.data[5] = 0;
  //  frame.data[6] = 0;
  //  frame.data[7] = 0;
  //
  //  can.sendMessage(&frame);
  //  delay(10);
  //  if (can.readMessage(&frame) == MCP2515::ERROR_OK) {
  //    Serial.print("Curent");
  //    Serial.print(" ");
  //    //                  for (int ii=1; ii<8;ii++){
  //    //                    Serial.print(ii);
  //    //                    Serial.print(" ");
  //    //                  Serial.print(frame.data[ii]);
  //    //                  Serial.print(" ");}
  //    cur = frame.data[2];
  //    cur = cur + (frame.data[3] << 8);
  //    Serial.print(cur);
  //  }
  // передаем CAN сообщение

  //  for (int i = 0; i != 4; i++) {
  //
  uint32_t speedcontrol = 1000;
  frame.can_id = motor_id[0];
  frame.can_dlc = 8;

  // frame.data[0] = 0x90;

  // frame.data[1] = 0;
  // frame.data[2] = 0;
  // frame.data[3] = 0;
  // frame.data[4] = 0;
  // frame.data[5] = 0;
  // frame.data[6] = 0;
  // frame.data[7] = 0;

  frame.data[0] = 0xA2;
  frame.data[1] = 0x00;
  frame.data[2] = 0x00;
  frame.data[3] = 0x00;
  frame.data[4] = *(uint8_t *)(&speedcontrol);
  frame.data[5] = *((uint8_t *)(&speedcontrol) + 1);
  frame.data[6] = *((uint8_t *)(&speedcontrol) + 2);
  frame.data[7] = *((uint8_t *)(&speedcontrol) + 3);

  can.sendMessage(&frame);
  delay(3);

  frame.data[0] = 0x9C;
  frame.data[1] = 0x00;
  frame.data[2] = 0x00;
  frame.data[3] = 0x00;
  frame.data[4] = 0x00;
  frame.data[5] = 0x00;
  frame.data[6] = 0x00;
  frame.data[7] = 0x00;
  can.sendMessage(&frame);
  // if (can.readMessage(&frame) == MCP2515::ERROR_OK) {
  //   Serial.print("send");
  //   Serial.print(" ");
  //               for (int ii=1; ii<8;ii++){
  //                 Serial.print(ii);
  //                 Serial.print(" ");
  //               Serial.print(frame.data[ii]);
  //               Serial.print(" ");}
  //   enc = frame.data[4];
  //   enc = enc + (frame.data[5] << 8);
  //   Serial.println(enc);
  // }
  //    Serial.print("enc: ");
  //   Serial.print(enc);
  //    Serial.print(" ");
  //    a[i] = abs(enc[i]/66)-_speed;
  //    Serial.print(a[i]);
  //
  //
  //    frame.can_id = motor_id[i];
  //    frame.can_dlc = 8;

  //
  //    if (can.readMessage(&frame) == MCP2515::ERROR_OK) {
  //      Serial.print("send2 ");
  //      for (int ii = 0; ii < 8; ii++) {
  //        Serial.print(ii);
  //        Serial.print(" ");
  //        Serial.print(frame.data[ii]);
  //        Serial.print(" ");
  //      }
  //
  //    }
  //    delay(10);
  //
  //            frame.data[0] = 0xA1;
  //        frame.data[1] = 0x00;
  //        frame.data[2] = 0x00;
  //        frame.data[3] = 0x00;
  //        frame.data[4] = *(uint8_t*)(&tor);
  //        frame.data[5] = *((uint8_t*)(&tor) + 1);
  //        frame.data[6] = 0x00;
  //        frame.data[7] = 0x00;
  //        can.sendMessage(&frame);

  //    uint32_t speedcontrol = -100000 ;
  ////    if (i>=2){
  ////      speedcontrol = -speedcontrol;
  ////      }
  //
  //        frame.data[0] = 0xA2;
  //        frame.data[1] = 0x00;
  //        frame.data[2] = 0x00;
  //        frame.data[3] = 0x00;
  //        frame.data[4] = *(uint8_t*)(&speedcontrol);
  //        frame.data[5] = *((uint8_t*)(&speedcontrol) + 1);
  //        frame.data[6] = *((uint8_t*)(&speedcontrol) + 2);
  //        frame.data[7] = *((uint8_t*)(&speedcontrol) + 3);
  //
  //   can.sendMessage(&frame);  //передаем CAN сообщение
  //    if (can.readMessage(&frame) == MCP2515::ERROR_OK) {
  //      Serial.print("send3 ");
  //      for (int ii = 0; ii < 8; ii++) {
  //        Serial.print(frame.data[ii]);
  //        Serial.print(" ");
  //      }
  //    }
  //  }
  //
  delay(10);
  //   delayMicroseconds(100);
  //  Serial.println();
}
*/

#include <Arduino.h>

void setup() {
  Serial.begin(115200);

}
long iter = 0;
  static uint8_t buffer[16];
  
void loop() {
//   Serial.print("T");
//  Serial.print(iter);
//  Serial.print("E");
//  Serial.println(int(1000*sin(millis()/1000.0)));
//  delay(50);
//  iter +=1;
 size_t index = 0;
  if (Serial.available() > 0){
  while (Serial.available() > 0) {
    buffer[index++] = Serial.read();}}

  for (int i = 0; i<16; i +=1){
    Serial.print(buffer[i]);
  Serial.print(" ");
   Serial.print(buffer[i]+ (buffer[i+1]<<8));
   Serial.print(" ");
}Serial.println("");
    
}
