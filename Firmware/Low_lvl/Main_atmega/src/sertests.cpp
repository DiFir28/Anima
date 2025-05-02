
#include "setup/config.h"
#include "setup/math.cpp"
#include "movement/movement.h"
#include "Sensors/Gyro/gyro.h"
#include "Leds/leds.h"
#include "Sensors/Line_circle/line.h"
#include <Servo.h>

//  line_circle circle;

Leds leds(8, 33);

char output[20]="";

Servo motorA;


int ret_i = 0;
    short controlPin[3] = {22, 23, 24};
    short slavPins[2] = {A0, A1};
    struct lisens line_sensors[16];

float ball_angle = 0.0;
int getting = 0;
float goals[] = {0.0, 0.0};
bool have_ball = 0;

void setConfigurate(int conf)
{
    for (int conf_i = 2; conf_i > -1; conf_i--)
    {
        digitalWrite(controlPin[conf_i], (conf >= pow(2, conf_i)));
        conf = conf - pow(2, conf_i) * (conf >= pow(2, conf_i));
    }
}
void get_from_cam()
{  
  if (Serial.available()>0){

    char get[12] = "";
    while(Serial.available()>0){int bytesRead = Serial.readBytesUntil('\n', get, 12 - 1);}
     Serial.println(atoi(get));
     

    ball_angle = ((atoi(get))/1000.0);
    Serial.print(ball_angle);
    Serial.print(" ");
    Serial.print(gyro);}
    leds.on(1, 20, 20, 0);
  // }else{
  //   leds.on(0, 0, 0, 20);
  // }
  for(short i = 0; i <20; i++){
    output[i]='\0';
  }
  
}


unsigned long last_time = 0;
void setup()
{
  gyro_init();
  Serial.begin(115200);
  canInit();
  pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(0, stop, FALLING);
  attachInterrupt(1, play, RISING);
  stop();
  leds.on(0, 2, 2, 0);
  for(int i = 0; i<3 ; i++){
    pinMode(controlPin[i], OUTPUT);
  }
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  // motorA.attach(18);
  // motorA.writeMicroseconds(1900);
  // delay(2000);
  // motorA.writeMicroseconds(1000);
  // delay(2000);
  // motorA.writeMicroseconds(1400);
  // delay(2000);
  // motorA.writeMicroseconds(0);
  // delay(2000);



  //   while (!Serial.available()){
  //     Serial.end();
  //     delay(5);
  // Serial.begin(115200);
  // delay(5);
  //   }
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

}



float move_ang = 0.0;
float yaw_ang = 0.0;
float move_speed = 4.0;

void loop()
{

  Serial.print("  ");
  
    //    get_from_cam();

  
    // go(radvec(0,0),  ball_angle);
    
  // }
  // else
  // {
  //   // Serial.print(" Waiting for button press");
  // }

  // digitalWrite(LED_BUILTIN, LOW);


  // delay(3);

  // Serial.println("");
  // Serial2.println(123567);
  // char a = Serial2.read();
  // Serial.print(".");
  // Serial.println(Serial.available());
  //  Serial.println(a);
  delay(1);




// motorA.writeMicroseconds(1000);
Serial.print("\t");
  for(int i =0; i<8; i++)
{setConfigurate(i);
  Serial.print(analogRead(A0));
Serial.print("\t");
Serial.print(analogRead(A1));
Serial.print("\t");
} 
// setConfigurate(0);
// setConfigurate(0);
// Serial.print(analogRead(A0));
// Serial.print("\t");
// Serial.print(analogRead(A1));
// Serial.print("\t");



// char millis_char[7] = "";
// itoa(millis(), millis_char, DEC);
// strcat(output, millis_char);
// strcat(output, ": ");
// Serial.print(": ");
//    Serial.print(millis());
//    Serial.print(" ");
//   Serial.print(": ");
  //  Serial.print(millis()-last_time);
  //  Serial.print(": ");
  //  last_time = millis();

    // gyro = gyro_read();
  // Serial.print("Gyro: ");
  // Serial.println(gyro);
  // char se[5];
// strcat(output,"Gyro: ");
// char* gr = 0;
// if (gyro !=0.0){
// char gyro_char[6]="";
//   dtostrf(gyro, int(log10(abs(int(gyro))))+3,2, gyro_char);

// strcat(output,gyro_char);
// }else{
//     strcat(output,"0.00");
//   }
// itoa(int(gyro),gyro_char, DEC);
// strcat(output, gyro_char);
//   strcat(output," ");
  // itoa(int(gyro * 1000), se, DEC);
  // Serial.write(se);

  

  // if (act)
  // {
  //   if (have_ball)
  //   {
  //   }
  //   else
  //   {
  //     move_ang = ball_angle*1.1 +25;
  //     yaw_ang = 0;
  //   }
    //go(radvec(0 + M_PI/2 * int(millis()%4000/1000), 0), ball_angle);
}