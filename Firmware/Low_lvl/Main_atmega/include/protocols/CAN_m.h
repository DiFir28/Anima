#pragma once

#include <mcp2515.h>

#define TOWATRDS_END 1

typedef struct data_m
{
    short n;
    short n_byte;

} data_m;

typedef struct rule_m
{
    data_m data[8];
} rule_m;

class comand_m
{
public:
    comand_m(int, ...);

    rule_m rule;
    void create_rule(short);

    short count_data;
    short data_weight[8] = {-1};
    short sum_data_weight = 0;
};

comand_m::comand_m(int count, ...)
{
    this->count_data = count;
    va_list ap;
    va_start(ap, count);
    for (int i = 0; i < count; i++)
    {
        data_weight[i] = va_arg(ap, int);
        sum_data_weight += data_weight[i];
    }
    va_end(ap);
}

void comand_m::create_rule(short q)
{

    for (int i = 0; i < 8; i++)
    {
        rule.data[i].n = 0;
    }

    switch (q)
    {
    case TOWATRDS_END:
        short data_i = count_data;
        short byte_i = 7;
        for (int i = count_data - 1; i >= 0 ; i--){
            for (int j = data_weight[i]; j >= 0; j--){
                rule.data[byte_i].n = i;
                rule.data[byte_i].n_byte = j;
                byte_i--;
            }
        }

        break;

    default:
        break;
    }
}



