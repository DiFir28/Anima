#pragma  once
#include <Arduino.h>
#include "typedef.h"

short sign(int num){
    return (num > 0)*2 - 1;
}

ang_t between(ang_t first_angle, ang_t second_angle){
    ang_t output = int(first_angle - second_angle);
    output = (360 - abs(output)) % 180 * (abs(output) > 180) * sign(-output) + !(abs(output) > 180) * output;
    return output;
}

