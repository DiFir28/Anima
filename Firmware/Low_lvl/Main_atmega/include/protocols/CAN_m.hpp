#pragma once

#include <mcp2515.h>

MCP2515 can(53);

int motor_id[] = {0x141, 0x142, 0x143, 0x144};
void canInit()
{
    SPI.begin();
    can.reset();
    can.setBitrate(CAN_1000KBPS, MCP_16MHZ);
    can.setNormalMode();
    for (short i = 0; i < 4; i++)
    {
        Serial.print(motor_id[i]);
        Serial.print(" ");
    }
}

// #define TOWATRDS_END 1

// typedef struct data_m
// {
//     short n;
//     short n_byte;

// } data_m;

// typedef struct rule_m
// {
//     data_m data[8];
// } rule_m;

// class comand_m
// {
// public:
//     comand_m(int, ...);

//     rule_m send_rule, recv_rule;
//     void create_rule(rule_m *rule, short guide);

//     short count_data;
//     short data_weight[8] = {-1};
//     short sum_data_weight = 0;
// };
// int a = std::upper_bound();
