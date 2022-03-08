#ifndef screens_h
#define screens_h

#include "mbed.h"
#include "all_config.h"

// Classe Actuators
class Screens

{

public:

    // Construtor da classe
    Screens();

    //Initialization of LCD display
    void screen_1(void);
    void screen_2(void);
    void screen_3(void);
    void screen_4(void);
    void screen_5(void);
    void screen_6(void);
    void screen_7(int pulse);
    void screen_8(int pulse);
    void clean(void);

    TextLCD display_LCD;

private:

};

#endif