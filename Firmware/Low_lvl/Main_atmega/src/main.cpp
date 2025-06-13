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

//char get[15] = "";


int get_arr[] = {0,0,0,0, 0};
float get_rbp[] = {0,0,0,0};
const char* gett;

size_t countChar(const char* str, char target) {
  size_t count = 0;
  for (size_t i = 0; str[i] != '\0'; i++) {
      if (str[i] == target) {
          count++;
      }
  }
  return count;
}

void convert(int count){
  if (countChar(gett, ',') != count+1){
    return;
  }
  char* sep =strchr(gett, ',');
  for(int i = 0; i<count; i++){
    char* l_sep = sep;
    
     sep = strchr(sep+1, ',');
    char buf[7] = "";
    strncpy(buf, l_sep+1, sep - l_sep-1);
    get_arr[i] = atoi(buf );
    
    } 
  }



int drib_pow = 1450;

unsigned long last_time = 0;
void setup()
{
  canInit();
  gyro_init();

  motorA.attach(26);
  motorA.writeMicroseconds(1900);
  delay(2000);
  motorA.writeMicroseconds(1000);
  delay(2000);
  motorA.writeMicroseconds(1400);
  delay(2000);
  motorA.writeMicroseconds(0);
  delay(2000);

  
  pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(0, stop, FALLING);
 // attachInterrupt(1, play, RISING);
  stop();

  leds.on(0, 2, 2, 0);

  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);
  pinMode(24,OUTPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  pinMode(4,INPUT);

  RBP_Serial.begin(115200);
  Serial.begin(115200);
 
  leds.on(0, 0, 100, 100);
  delay(1000);  
  

}

bool play = 0;
bool last_4 = 0;

unsigned long drib_update = 0;

float curl_ball_ang = 0.0;
float move_ang = 0.0;
float yaw_ang = 0.0;
float move_speed = 4.0;

int drib_flag = 1;

float aang = 0.0;

void loop()
{

  motorA.writeMicroseconds(1480 - get_arr[3]);
  Serial.print(play);

  // RBP_Serial.print("  ");
  
  //get_from_cam();
       
  //go(radvec(ball_angle, 0.4 * (abs(between(gyro_read(), ball_angle)) < 0.3)), between(0, ball_angle));
  //go(radvec(2,1),1.0);

   //go(radvec(between(0, ball_angle),    1.2 * (abs(between(gyro_read(), ball_angle)) < 0.8) ),  between(0, ball_angle));


  if (play){
    go( radvec(get_arr[0]/1000.0,get_arr[1]/1000.0 ), get_arr[2]/1000.0, get_arr[4]/1000.0);
  }else{
    go(radvec(0,0),0);
  }
  Serial.print("accept^");
  Serial.print(" ");
  Serial.print(get_arr[0]/1000.0);
  Serial.print(" ");
  Serial.print(get_arr[1]/1000.0);
  Serial.print(" ");
  Serial.print(get_arr[2]/1000.0);
  Serial.print(" ");
  Serial.print(1450 - get_arr[3]);
  Serial.print(" ");

  if (digitalRead(4) && !last_4){
    play = !play;
  }
  last_4 = digitalRead(4);

  RBP_Serial.print("   ");

  Serial.print(gyro_read());
  RBP_Serial.println( gyro_read() );


  if (RBP_Serial.available() > 0) {
    String received = RBP_Serial.readStringUntil('\n');
    //received.trim();    
    Serial.print(" ");
    Serial.print(received);
    gett =  received.c_str();

    convert(5);
    

  }
  Serial.println("");

  for(int i =0; i<4;i++){
    Serial.print(get_arr[i]);
    Serial.print(" ");
    }

  RBP_Serial.print(" ");
  // RBP_Serial.print(get);
  RBP_Serial.print(" ");
  RBP_Serial.print(drib_pow);
  RBP_Serial.print(" ");  
  RBP_Serial.print(ball_len);
  RBP_Serial.println(" ");
  delay(20);

}
