#ifndef LiquidCrystalDisplay_h
#define LiquidCrystalDisplay_h

#include <LiquidCrystal_I2C.h>
#include <string>

class LiquidCrystalDisplay
{
private:
    LiquidCrystal_I2C *lcd;
public:
    LiquidCrystalDisplay();

    void init();
    void print(int row, std::string data, bool clear = false);
};

#endif
