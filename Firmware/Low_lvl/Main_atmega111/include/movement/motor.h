#include "setup/config.h"
#include "protocols/CAN_m.hpp"

class Motor{
public:
    Motor(short ID, float ang):ID(ID),ang(ang){
        msg.can_id = ID;
    }
    void go(float mpm);
    
    void update();
  
private:  
    short ID;
    float ang;
    struct can_frame msg;
    unsigned long last_time_change = 0;
    unsigned long last_tick = 0, tick = 0, dtick;
    float kp =0, ki =0, kd=0;
    
    float mps, rpm, curr_rpm;
    long speed;
    
};

void Motor::go(float mps){
    mps = mps;
    rpm = mps*10000/54/M_PI * 60;
    curr_rpm = abs(last_tick - tick) /pow(2,16) * (60000 / (millis()-last_time_change)) ;
    speed = (  rpm + (rpm - curr_rpm) )*100;
    msg.can_dlc = 8;
    msg.data[0] = 0xA2;
    msg.data[1] = 0x00;
    msg.data[2] = 0x00;
    msg.data[3] = 0x00;
    msg.data[4] = *(uint8_t*)(&speed);
    msg.data[5] = *((uint8_t*)(&speed) + 1);
    msg.data[6] = *((uint8_t*)(&speed) + 2);
    msg.data[7] = *((uint8_t*)(&speed) + 3);
    can.sendMessage(&msg);
    last_time_change = millis();
    last_tick = tick;
    
}

void Motor::update(){
    msg.can_dlc = 8;
    msg.data[0] = 0x90;
    msg.data[1] = 0;
    msg.data[2] = 0;
    msg.data[3] = 0;
    msg.data[4] = 0;
    msg.data[5] = 0;
    msg.data[6] = 0;
    msg.data[7] = 0;

    can.sendMessage(&msg);
    delay(5);
    if (can.readMessage(&msg) == MCP2515::ERROR_OK) {
      //enc[i] = frame.data[4];
      tick = msg.data[4] + (msg.data[5] << 8);
    }
}