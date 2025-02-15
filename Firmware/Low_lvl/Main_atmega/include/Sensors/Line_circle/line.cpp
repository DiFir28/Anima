#include "line.h"

// void lisenses::calib()
// {

//     for (int c = 0; c < 8; c++)
//     {
//         setConfigurate(c);
//         delay(1);
//         for (int step = 0; step < 4; step++)
//         {
//             line_sensors[step * 8 + c].min_value = min(analogRead(slavPins[step]), line_sensors[step * 8 + c].min_value);
//             line_sensors[step * 8 + c].max_value = max(analogRead(slavPins[step]), line_sensors[step * 8 + c].max_value);
//             line_sensors[step * 8 + c].threshold_value = int((line_sensors[step * 8 + c].min_value + line_sensors[step * 8 + c].max_value) / 1.8);
//             line_sensors[step * 8 + c].broken = ((line_sensors[step * 8 + c].min_value + line_sensors[step * 8 + c].max_value) < 100);
//             if (line_sensors[step * 8 + c].broken)
//             {
//                 Serial.println("ERR_LINE");
//             }
//         }
//     }
//     Serial.print("NewT:");
//     for (int i = 0; i < 32; i++)
//     {
//         Serial.print(line_sensors[i].threshold_value);
//         Serial.print(" ");
//     }
// }

// void lisenses::init()
// {
//     for (short ili = 0; ili < 3; ili++)
//     {
//         pinMode(controlPin[ili], OUTPUT);
//     }
//     for (short ili = 0; ili < 2; ili++)
//     {
//         pinMode(slavPins[ili], INPUT);
//     }

//     for (short ili = 0; ili < 16; ili++)
//     {
//         line_sensors[ili].value = 0;
//         line_sensors[ili].bool_value = false;

//             line_sensors[ili].vector.ang = 22.5*ili*DEG_TO_RAD;


//         if (min(abs(ili - 32), abs(ili)) <= 1)
//         {
//             line_sensors[ili].vector.lenght = all_len[min(abs(ili - 32), abs(ili))];
//         }
//         else
//         {
//             line_sensors[ili].vector.lenght = all_len[2];
//         }
//     }
// }






void line_circle::setConfigurate(int conf)
{
    for (int conf_i = 2; conf_i > -1; conf_i--)
    {
        digitalWrite(controlPin[conf_i], (conf >= pow(2, conf_i)));
        conf = conf - pow(2, conf_i) * (conf >= pow(2, conf_i));
    }
}

// void lisenses::read_line()
// {
//     ret_i = 0;

//     for (int c = 0; c < 8; c++)
//     {
//         setConfigurate(c);
//         delay(1);
//         for (int step = 0; step < 4; step++)
//         {
//             line_sensors[step * 8 + c].value += int(0.95 * (analogRead(slavPins[step]) - line_sensors[step * 8 + c].value));
//             line_sensors[step * 8 + c].bool_value = (line_sensors[step * 8 + c].value > line_sensors[step * 8 + c].threshold_value);

//             if (!line_sensors[step * 8 + c].broken)
//             {

//                 if (line_sensors[step * 8 + c].bool_value or (millis() - line_sensors[step * 8 + c].time_high < 200))
//                 {
//                     livectors[ret_i] = line_sensors[step * 8 + c].vector;
//                     if (line_sensors[step * 8 + c].bool_value)
//                         line_sensors[step * 8 + c].time_high = millis();
//                 }
//                 ret_i += line_sensors[step * 8 + c].bool_value;
//             }

//             // for (int i = 0; i < 32; i++)
//             // {
//             //     Serial.print(line_sensors[i].vector.angle);
//             //     Serial.print(", ");
//             //     Serial.print(line_sensors[i].vector.lenght);
//             //     Serial.print(", ");
//             //     Serial.print(line_sensors[i].value);
//             //     Serial.print("/");
//             // }
//             // Serial.println("}");
//         }
//     }
// }

// vec lisenses::get_line()
// {
//     vec ret;

//     int lisin = 0;
//     int licos = 0;
//     Serial.print(" Line: ");

//     if (ret_i == 0)
//     {
//         ret.ret = 0;
//         ret.angle = 0;
//         ret.lenght = -1;
//         Serial.print(ret.angle);
//         Serial.print(" ");
//         Serial.print(ret.lenght);
//         Serial.print(" ");

//         return ret;
//     }
    
//     ret.ret = 1;

//     for (int i = 0; i < ret_i; i++)
//     {

//         lisin += sin(livectors[i].angle * DEG_TO_RAD) * livectors[i].lenght;
//         licos += cos(livectors[i].angle * DEG_TO_RAD) * livectors[i].lenght;
//         //  Serial.print();
//         //  Serial.print(" ");
//     }

//     ret.angle = (atan2((lisin), (licos)) * RAD_TO_DEG);
//     ret.lenght = sqrt(lisin * lisin + licos * licos) / ret_i;

//     // if (side == 0)
//     // {
//     //     side = sign(ret.angle);
//     // }
//     // else if (side != sign(ret.angle))
//     // {
//     //     ret.angle = -ret.angle;
//     //     side = sign(ret.angle);
//     // }

//     Serial.print(ret.angle);
//     Serial.print(" ");
//     Serial.print(ret.lenght);
//     return ret;
// }

// vec lisenses::update()
// {
//     read_line();
//     return get_line();
// }
