#pragma once

#include "motor.h"
#include "Setup/math.cpp"
#include "Sensors/Gyro/gyro.h"

int act = 0, flag = 0;

Motor motor[] = {
    create_motor(0x141, DEG_TO_RAD * (63 - 90)),
    create_motor(0x142, DEG_TO_RAD * (127 - 90)),
    create_motor(0x143, DEG_TO_RAD * (233 - 90)),
    create_motor(0x144, DEG_TO_RAD * (297 - 90))};

float gyro;
float a = 5 * M_PI / 2;
void go(Vec v, float yaw)
{

    v.calcxy();
    v = v.rot(-gyro_read());
    Serial.print(" ");
    // Serial.print(v.ang - gyro_read());
    Serial.print(" ");
    for (short i = 0; i < 4; i++)
    {
        if (i == break_m)
            continue;
        motor[i].go(v, yaw,gyro_read());
        Serial.print(cos(between(motor[i].ang, v.ang)) * v.len*100);
        Serial.print(" ");
    }


    // for (short i = 0; i < 4; i++)
    // {
    //     if (i == break_m)
    //         continue;

    //     motor[i].go(v.ang - gyro_read()), v.len);
    //     Serial.print(cos(between(motor[i].ang, v.ang - gyro_read())) * v.len*100);
    //     Serial.print(" ");
    // }
}

void stop()
{
    for (short i = 0; i < 4; i++)
    {
        motor[i].setSpeed(0);
    }
    act = (act + flag) % 2;
    flag = 0;
}

void play()
{
    flag = 1;
}
