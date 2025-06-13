#pragma once

#include "Setup/config.h"
#include "Setup/math.cpp"
#include "Setup/PID.h"
#include "Protocols/CAN_m.hpp"

PID e();

class Motor
{
public:
    Motor(int ID, float ang) : ID(ID), ang(ang)
    {
        msg.can_id = ID;
    }
    void go(Vec v, float yaw, float gyro, float qqq);

    void update();
    void setSpeed(float mps);
    int ID;
    float ang;
private:
    struct can_frame msg;
    unsigned long last_time_change = 0;
    unsigned long last_tick = 0, tick = 0, dtick;
    float kp = 0, ki = 0, kd = 0, up = 0;
    float rkp = 0.8, rki = 0.00001, rkd = 4, rup = 0, rI = 0;

    float mps, rps, curr_rpm, dps;
    long speed;
};

void Motor::go(Vec v, float yaw, float gyro, float qqq){
    static float rerr = 0, lrerr = 0;
    // static float err = 0, lerr = 0;
    rerr = between(yaw, gyro);
    rup = constrain(rkp * rerr + rkd * (lrerr - rerr) + rki * rI,-qqq,qqq);
    up = constrain(cos(between(ang, v.ang)) * v.len, -5, 5);

    // Serial.print("\t");
    // Serial.print(rup);
    // Serial.print("\t");

    dps = rup+up;
    setSpeed(dps);
    lrerr = rerr;
    rI += rerr;
}

void Motor::setSpeed(float dps)
{
    // mps = mps;
    // rps = mps * 10000 / 54 / M_PI;
    // curr_rpm = abs(last_tick - tick) /pow(2,16) * (60000 / (millis()-last_time_change)) ;
    
    speed = (dps) * 100 * 360;

    msg.can_dlc = 8;
    msg.data[0] = 0xA2;
    msg.data[1] = 0x00;
    msg.data[2] = 0x00;
    msg.data[3] = 0x00;
    msg.data[4] = *(uint8_t *)(&speed);
    msg.data[5] = *((uint8_t *)(&speed) + 1);
    msg.data[6] = *((uint8_t *)(&speed) + 2);
    msg.data[7] = *((uint8_t *)(&speed) + 3);
    can.sendMessage(&msg);
    last_time_change = millis();
    last_tick = tick;
    // Serial.print(" ");
    // Serial.print(ID);
    // Serial.print(": ");
    // Serial.print(dps);
    // Serial.print("   ");
}

void Motor::update()
{
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
    if (can.readMessage(&msg) == MCP2515::ERROR_OK)
    {
        // enc[i] = frame.data[4];
        tick = msg.data[4] + (msg.data[5] << 8);
    }
}

Motor create_motor(int ID, float ang)
{
    Motor result(ID, ang);
    return result;
}