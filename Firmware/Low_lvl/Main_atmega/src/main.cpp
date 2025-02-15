#include "setup/config.h"
#include "setup/math.cpp"
#include "movement/movement.h"
#include "Sensors/Gyro/gyro.h"
#include "Leds/leds.h"
#include "Sensors/Line_circle/line.h"

//  line_circle circle;

Leds leds(8, 33);

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
  Serial.println("GET");
  leds.on(0, 20, 0, 0);
  unsigned long start_read = millis();
  while ((Serial.read() == -1) and (millis() - start_read < 200))
  {
  }
  if (Serial.read() != -1)
  {
    leds.on(0, 0, 20, 0);
    char get[17] = "";
    int bytesRead = Serial.readBytesUntil('\n', get, 17 - 1);
    ball_angle = atoi(get)/80;
    leds.on(1, 0, atoi(get), 0);
  }else{
    leds.on(0, 0, 0, 20);
  }
}


unsigned long last_time = 0;
void setup()
{
  gyro_init();
  Serial.begin(9600);
  canInit();
  pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(0, stop, FALLING);
  attachInterrupt(1, play, RISING);
  stop();
  leds.on(0, 2, 2, 0);

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
  while(digitalRead(4)==1){}
}



float move_ang = 0.0;
float yaw_ang = 0.0;
float move_speed = 4.0;

void loop()
{
//   for(int i =0; i<8; i++)
// {setConfigurate(i);
// Serial.print(analogRead(A0));
// Serial.print("\t");
// } 

//   for(int i =0; i<8; i++)
// {setConfigurate(i);
// Serial.print(analogRead(A1));
// Serial.print("\t");
// } 

setConfigurate(0);
Serial.print(analogRead(A0));
Serial.print("\t");
Serial.print(analogRead(A1));
Serial.print("\t");



// get_from_cam();

  //  Serial.print(millis());
  //  Serial.print(" ");
  //  Serial.print(millis()-last_time);
  //  Serial.print(": ");
  //  last_time = millis();

  // gyro = gyro_read();
  // char se[5];

  // // Serial.print("Gyro: ");
  // // Serial.print(gyro);

  // itoa(int(gyro * 1000), se, DEC);
  // // Serial.write(se);

  

  // if (act)
  // {
  //   if (have_ball)
  //   {
  //   }
  //   else
  //   {
  //     move_ang = ball_angle * 1.1 - sign(ball_angle) * 5;
  //     yaw_ang = move_ang;
  //   }
  //   go(radvec(move_ang, move_speed), yaw_ang);
  // }
  // else
  // {
  //   // Serial.print(" Waiting for button press");
  // }

  // digitalWrite(LED_BUILTIN, LOW);


  delay(3);

  Serial.println(" ");
}
