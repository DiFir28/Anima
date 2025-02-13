#pragma once

#include "motor.h"



int act = 0, flag =0;

Motor motor[]={
    create_motor(0x141, 1.0996), 
    create_motor(0x142, 1.0996), 
    create_motor(0x143, 4.0666), 
    create_motor(0x144, 5.1836)
};

void stop(){
    for(int i=0;i<4;i++){
        motor[i].go(0);
    }
    act = (act+flag)%2;
    flag = 0;

}

void play(){
    flag = 1;
}

