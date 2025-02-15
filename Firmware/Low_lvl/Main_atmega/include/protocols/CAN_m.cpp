#pragma once

#include "CAN_m.hpp"

// comand_m::comand_m(int count, ...)
// {
//     this->count_data = count;
//     va_list ap;
//     va_start(ap, count);
//     for (int i = 0; i < count; i++)
//     {
//         data_weight[i] = va_arg(ap, int);
//         sum_data_weight += data_weight[i];
//     }
//     va_end(ap);
// }

// void comand_m::create_rule(rule_m *rule, short guide)
// {
//     rule_m i_rule = *rule;

//     for (int i = 0; i < 8; i++)
//     {
//         i_rule.data[i].n = 0;
//     }

//     switch (guide)
//     {
//     case TOWATRDS_END:
//         short data_i = count_data;
//         short byte_i = 7;
//         for (int i = count_data - 1; i >= 0 ; i--){
//             for (int j = data_weight[i]; j >= 0; j--){
//                 i_rule.data[byte_i].n = i;
//                 i_rule.data[byte_i].n_byte = j;
//                 byte_i--;
//             }
//         }

//         break;

//     default:
//         break;
//     }
// }