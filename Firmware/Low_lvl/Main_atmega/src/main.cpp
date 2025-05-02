#include "setup/config.h"
#include "setup/math.cpp"
#include "movement/movement.h"
#include "Sensors/Gyro/gyro.h"
#include "Leds/leds.h"
#include "Sensors/Line_circle/line.h"
#include "Protocols/Serial.hpp"
#include <Servo.h>


//  line_circle circle;

Leds leds(8, 33);
Servo motorA;

char output[20]="";



int ret_i = 0;
    short controlPin[3] = {22, 23, 24};
    short slavPins[2] = {A0, A1};
    struct lisens line_sensors[16];

float ball_angle = 0.0;
int ball_len =0;
int getting = 0;
float goals[] = {0.0, 0.0};
bool have_ball = 0;

// void setConfigurate(int conf)
// {
//     for (int conf_i = 2; conf_i > -1; conf_i--)
//     {
//         digitalWrite(controlPin[conf_i], (conf >= pow(2, conf_i)));
//         conf = conf - pow(2, conf_i) * (conf >= pow(2, conf_i));
//     }
// }

char get[15] = "";

void get_from_cam()
{  
  if (Serial.available()>0){

    memset(get,0,strlen(get));
    while(Serial.available()>0){int bytesRead = Serial.readBytesUntil('\n', get, 15 - 1);} 
    char ang_get[6] = "";
    char len_get[6] = "";
    char* sep = strchr(get, ',');
    strncpy(ang_get, get, sep - get);

    if (strlen(get) >= 5){
      ball_angle = ((atoi(get))/1000.0);
      ball_len = (atoi(sep+1));
    }

    leds.on(1,0, (atoi(get))/600, 0);}

  for(short i = 0; i <20; i++){
    output[i]='\0';
  }
  
}

int drib_pow = 1450;

unsigned long last_time = 0;
void setup()
{
    motorA.attach(18);
  motorA.writeMicroseconds(1900);
  delay(2000);
  motorA.writeMicroseconds(1000);
  delay(2000);
  motorA.writeMicroseconds(1400);
  delay(2000);
  motorA.writeMicroseconds(0);
  delay(2000);
  // Serial.begin(115200);
  canInit();
  gyro_init();
  pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(0, stop, FALLING);
  attachInterrupt(1, play, RISING);
  stop();
  leds.on(0, 2, 2, 0);

  leds.on(0,20,0,20);
  leds.on(1,0,0,0);

  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);
  pinMode(24,OUTPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);


  pinMode(4,INPUT);
  // while(digitalRead(4)==1){}
  leds.on(0, 0, 0, 0);


     Serial.begin(115200);


    // while(Serial.available()<=0){
    //   Serial.println("66");
    //   delay(100);
    // }
    
    // char get[15] = " 1";
    // long sended = millis();
    
    // delay(2000);
    // Serial.println(sended);
    // Serial.readBytesUntil('\n', get, 15 - 1);
    // while(sended != atoi(get)){
      
    //   if (Serial.available() > 0){
    //     memset(get,0,strlen(get));
    //     int bytesRead = Serial.readBytesUntil('\n', get, 15 - 1);
    //     if (sended != atoi(get)){

    //       sended = millis();
    //       Serial.print(sended);
    //     }else{
    //       break;
    //     }   
    //   }
       
      
    //   delay(10);
    // }

    
    
    Serial.println(" Serial start ");
    delay(100);
    Serial.println(millis());
    leds.on(0, 0, 100, 100);
    delay(1000);

    

}

unsigned long drib_update = 0;

float curl_ball_ang = 0.0;
float move_ang = 0.0;
float yaw_ang = 0.0;
float move_speed = 4.0;

int drib_flag = 1;

float aang = 0.0;

void loop()
{
   motorA.writeMicroseconds(1150);

    // Serial.print("  ");
  
    //get_from_cam();

    
       
    //go(radvec(ball_angle, 0.4 * (abs(between(gyro_read(), ball_angle)) < 0.3)), between(0, ball_angle));

     go(radvec(between(0, ball_angle),   0.4 * (abs(between(gyro_read(), ball_angle)) < 0.2) ),  between(0, ball_angle));

  //   if (ball_len > 100){
    
  //   if (millis() - drib_update > 15){
  //   drib_pow += (drib_pow < 1450);
  //   drib_update = millis();
  // }
  //   leds.on(0,0,50,0);


  // if(digitalRead(4)==0 and drib_flag){
  //   drib_flag = 0;
    
  //   for (int i  = 1400; i>1250; i--){
  //     motorA.writeMicroseconds(i);
  //     delay(10);
  //     leds.on(0,0,100,250);
  //   }


  // }

  
  // }else{
  //   go(radvec(ball_angle, 0.1 * (abs(between(gyro_read(), ball_angle)) < 0.5)), between(0, ball_angle));
    
    // if (millis() - drib_update > 15){
    //   drib_pow -= (drib_pow > 1200);
    //   drib_update = millis();
    // }
   

  

    //get_serial();
    // leds.on(0, ser_get[0], ser_get[1],ser_get[2]);
    // for(int i =0 ; i< 3; i++){
    //     Serial.print(ser_get[i]);
    //     Serial.print("  ");

    // }




    // aang -= 0.01;
    // go(radvec(0,0), aang);
    // Serial.print(aang);


  
    
  // }
  // else
  // {
  //   // Serial.print(" Waiting for button press");
  // }

  // digitalWrite(LED_BUILTIN, LOW);


  // delay(3);

   //Serial.print(" ");
  // Serial2.println(123567);
  // char a = Serial2.read();
 //  Serial.print(millis());
  // Serial.print("Ang: ");
  // Serial.print(curl_ball_ang);
  //Serial.print(" Gyro: ");
//   Serial.print(" ");
   Serial.print( gyro_read() );
  //Serial.print(" ");
  // // Serial.print(get);
  Serial.print(" ");
  Serial.print(drib_pow);
  Serial.print(" ");  
  Serial.print(ball_len);
  Serial.println(" ");
  delay(5);

}
