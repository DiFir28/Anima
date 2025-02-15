#pragma once

#include "Setup/config.h"
#include "Setup/math.cpp"

struct lisens
{
  bool bool_value = 0;
  bool broken = 0;
  Vec vector;
  short analog_value = 0;
  short value = 1;
  short max_value = 0;
  short min_value = 0;
  short threshold_value = 200;
  unsigned long time_high = 0;
};

class line_circle
{
public:
    void init();
    void setConfigurate(int conf);
    void calib();

    Vec update();
    void read_line();
    Vec get_line();



private:

    int ret_i = 0;
    short controlPin[3] = {22, 23, 24};
    short slavPins[2] = {A0, A1};
    struct lisens line_sensors[16];
};