#include "RGBLED.h"
#include <Arduino.h>

void RGBLED::set_color(int red, int green, int blue)
{
    analogWrite(this->red_pin, red);
    analogWrite(this->green_pin, green);
    analogWrite(this->blue_pin, blue);
};

RGBLED::RGBLED(int red_pin, int green_pin, int blue_pin)
{
    this->red_pin = red_pin;
    this->green_pin = green_pin;
    this->blue_pin = blue_pin;
};

void RGBLED::set_intensity(int intensity)
{
    this->intensity = intensity;
};

void RGBLED::set_red()
{
    set_color(this->intensity, 0, 0);
};

void RGBLED::set_green()
{
    set_color(0, this->intensity, 0);
};

void RGBLED::set_blue()
{
    set_color(0, 0, this->intensity);
};
