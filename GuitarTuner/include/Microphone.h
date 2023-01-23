#ifndef Microphone_h
#define Microphone_h

#include <Arduino.h>
#include <arduinoFFT.h>

#define SAMPLES 256
#define SAMPLING_FREQUENCY 2048
#define SILENCE 3

class Microphone
{
private:
    arduinoFFT _FFT;
    ushort _microphone_pin;
    uint _sampling_period;

    double get_decibels();
    double get_peak();
public:
    Microphone(ushort microphone_pin);

    double detected_pick();
};

#endif
