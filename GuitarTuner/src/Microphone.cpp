#include "Microphone.h"
#include <Arduino.h>
#include <arduinoFFT.h>

// Reads microphone decibels
double Microphone::get_decibels()
{
    delay(50);
    return analogRead(_microphone_pin) * (5.0 / 1023.0);
};

// Using FFT, calculates the highest frequency
double Microphone::get_peak()
{
    delay(50);

    double vector_real[SAMPLES];
    double vector_imag[SAMPLES];
    unsigned long micro_seconds;
    for (unsigned int i = 0; i < SAMPLES; i++)
    {
        micro_seconds = micros();

        vector_real[i] = analogRead(_microphone_pin);
        vector_imag[i] = 0;

        // Wait time between SAMPLES
        while (micros() < (micro_seconds + _sampling_period))
        {
        }
    }

    // Perform FFT on SAMPLES
    _FFT.Windowing(vector_real, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    _FFT.Compute(vector_real, vector_imag, SAMPLES, FFT_FORWARD);
    _FFT.ComplexToMagnitude(vector_real, vector_imag, SAMPLES);

    // Find peak frequency
    return _FFT.MajorPeak(vector_real, SAMPLES, SAMPLING_FREQUENCY);
};

// Constructs microphone module on a given microphone_pin
Microphone::Microphone(ushort microphone_pin)
{
    _microphone_pin = microphone_pin;
    _FFT = arduinoFFT();
    _sampling_period = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
};

// Returns the highest calculated frequency (peak) if the read decibels are
// above the silence level, otherwise -1
double Microphone::detected_pick()
{
    uint decibels = int(get_decibels());
    if (decibels != SILENCE)
    {
        return get_peak();
    };

    return -1;
};
