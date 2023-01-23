// External libraries
#include <Arduino.h>
#include <Stepper.h>

// Custom dependencies
#include "Microphone.h"
#include "Notes.h"
#include "LiquidCrystalDisplay.h"
#include "RGBLED.h"

// RGB LED pins
#define RED_PIN 13
#define GREEN_PIN 14
#define BLUE_PIN 15

// Microphone pins
#define MICROPHONE_PIN 12
// A mean time to wait between microphone readings (microsecunds)
#define MEAN_TIME 4000000

// ULN2003 Motor Driver Pins
#define IN1 19
#define IN2 18
#define IN3 23
#define IN4 5
// Motor settings
#define MOTOR_STEPS_PER_REVOLUTION 2048
#define MOTOR_STEPS_COUNT 100
#define MOTOR_SPEED 5

// Initializes needed components and variables
Microphone microphone(MICROPHONE_PIN);
Stepper stepper(MOTOR_STEPS_PER_REVOLUTION, IN1, IN3, IN2, IN4);
LiquidCrystalDisplay lcd;
RGBLED rgb(RED_PIN, GREEN_PIN, BLUE_PIN);
Notes notes;

ulong last_check;

void tune_note(double peak, note note);

void setup()
{
    Serial.begin(115200);

    Serial.println("Initializing pins...");
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);

    Serial.println("Initializing the servo motor...");
    stepper.setSpeed(MOTOR_SPEED);

    Serial.println("Initializing LCD...");
    lcd.init();
    lcd.print(0, "Pluck a string", true);
    
    Serial.println("Guitar Tuner project succesfully started!");
    last_check = micros();
};

void loop()
{
    double peak = microphone.detected_pick();

    // If the peak was detected and the mean time between samples passed
    if (peak != -1 && micros() > last_check + MEAN_TIME)
    {
        // Tries to get the note for the detcted peak
        note note = notes.get_note_within_range(peak);

        if (note.valid)
        {
            std::string message = "String: " + std::string(note.name);
            Serial.println(message.c_str());
            lcd.print(0, message, true);

            last_check = micros();
            tune_note(peak, note);
        }
        else
        {
            rgb.set_blue();
            std::string message = "Pluck a string";
            Serial.println(message.c_str());
            lcd.print(0, message, true);
        };
    };
};

// Tunes the guitar according to given peak and required note
void tune_note(double peak, note note)
{
    // Cuts the peak in half if the microphone detected an octave
    if (peak >= (note.tuning * 2) - ALLOWED_RANGE &&
        peak <= (note.tuning * 2) + ALLOWED_RANGE)
        peak /= 2;
    
    // Difference in pitch that should be tuned accordingly
    double peak_difference = note.tuning - peak;
    // Pitch deviation higher than 0.5 is considered unacceptable and should be
    // tuned down or up
    if (abs(peak_difference) > 0.5)
    {
        rgb.set_red();
        // If the peak difference was positive, it should be tuned up,
        // otherwise it should be tuned down
        if (peak_difference > 0)
        {
            Serial.println("Tuning up...");
            lcd.print(1, "Tuning up...");
            stepper.step(-MOTOR_STEPS_COUNT);
        } else
        {
            lcd.print(1, "Tuning down...");
            Serial.println("Tuning down...");
            stepper.step(MOTOR_STEPS_COUNT);
        };
    } else {
        lcd.print(1, "In tune :)");
        rgb.set_green();
    };
};
