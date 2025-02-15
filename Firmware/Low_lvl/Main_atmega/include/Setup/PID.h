#pragma once

#include "Setup/config.h"

class PID{
    public:
    float kp = 0, ki = 0, kd = 0;


    PID(float kp = 0, float ki = 0, float kd = 0):kp(kp), ki(ki), kd(kd){}

    private:

    float err = 0, last_err = 0;
    float p_err = 0, i_err =0, d_err = 0;
    unsigned long last_time = 0;
    int dt(){
        return(millis()-last_time);
    }
    float calculate_p_up(float err){
        p_err = err;
        return kp * p_err;
    }
    float calculate_d_up(float err){
        d_err= kd * (last_err-err)/dt();
        return d_err;
    }

    float calculate_i_up(float err){
        i_err += err*dt();
        return i_err * ki;
    }

    void newErr(int nerr){
        last_err = err;
        err=nerr;
    }

    float up(int err){
        float result = calculate_p_up(err) + calculate_i_up(err) + calculate_d_up(err);
        last_time = millis();
        return result;
    }


};

PID create_pid(float kp = 0, float ki = 0, float kd = 0){
    PID result(kp, ki, kd);
    return result;
}