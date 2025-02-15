#pragma once

class Sensor
{
public:
    int (*read) (void);
    void (*init) ();
    Sensor(void (*init)(), int (*read)() ) : init(init), read(read) {}
    int value = 0;
    int raw = 0;
private:
};