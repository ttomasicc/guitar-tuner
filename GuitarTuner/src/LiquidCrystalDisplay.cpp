#include "LiquidCrystalDisplay.h"
#include <LiquidCrystal_I2C.h>
#include <string>

#define ROWS 2
#define COLS 16

// Constructs LiquidCrystalDisplay
LiquidCrystalDisplay::LiquidCrystalDisplay()
{
    lcd = new LiquidCrystal_I2C(0x27, COLS, ROWS);
};

// Initializes LiquidCrystalDisplay
void LiquidCrystalDisplay::init()
{
    lcd->init();
    lcd->backlight();
    lcd->clear();
};

// Prints given data string to a specified row [0, 1]
// optionally clears the display (default is false)
void LiquidCrystalDisplay::print(int row, std::string data, bool clear)
{
    if (clear)
    {
        lcd->clear();
    };

    lcd->setCursor(0,row);
    lcd->print(data.c_str());
};
