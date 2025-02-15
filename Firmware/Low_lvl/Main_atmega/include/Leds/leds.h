#ifndef _leds_H_
#define _leds_H_

#include "Adafruit_NeoPixel.h"
// #include "geometry.h"

class Leds
{
public:
    Leds(int pixeles, int LED_PIN){
        pixeles = pixeles;
        _strip = Adafruit_NeoPixel(pixeles, LED_PIN, NEO_GRB + NEO_KHZ800);
        _strip.begin();
        off();
    }
    void off(){ // выключение всех неопикселей
        for (int i = 0; i < pixeles; i++)
        {
            _strip.setPixelColor(i, _strip.Color(0, 0, 0));
            _strip.show();
        }
    }
    void on(int _port, int _red, int _green, int _blue)
    { // включение на конкретнй цвет двух неопикселей с одинаковым индексом
        _strip.setPixelColor(_port, _strip.Color(_red, _green, _blue));
        _strip.show();
    }
    void colorWipe(int _red, int _green, int _blue, unsigned long wait_ms);

private:
    int i = 0;
    unsigned long time_last_change = 0;
    int first = 100;
    int last = 0;
    int pixeles;
    Adafruit_NeoPixel _strip;
};

#endif // _leds_H_