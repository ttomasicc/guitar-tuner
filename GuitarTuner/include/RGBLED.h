#ifndef RGBLED_h
#define RGBLED_h

#include <Arduino.h>

class RGBLED
{
private:
    int intensity = 150;
    int red_pin = -1;
    int green_pin = -1;
    int blue_pin = -1;

    void set_color(int red, int green, int blue);
public:
    RGBLED(int red_pin, int green_pin, int blue_pin);

    void set_intensity(int intensity);
    
    void set_red();
    void set_green();
    void set_blue();
};

#endif
