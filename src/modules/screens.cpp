#include "screens.h"

Screens::Screens() : display_LCD(LCD_0, LCD_1, LCD_2, LCD_3, LCD_4, LCD_5){

display_LCD.cls();

}

void Screens::clean(void){

    display_LCD.cls();

}

void Screens::screen_1(void){

  display_LCD.locate(5, 0);
  display_LCD.printf("Hello!\n");
  display_LCD.locate(1, 1);
  display_LCD.printf("Press to start\n");

}

void Screens::screen_2(void){

    display_LCD.locate(0, 0);
    display_LCD.printf("Press to select\n");
    display_LCD.locate(0, 1);
    display_LCD.printf("the desired wave\n");

}

void Screens::screen_3(void){

    display_LCD.locate(3, 0);
    display_LCD.printf("Triangular\n");

    display_LCD.locate(1, 1);
    display_LCD.printf("Ramp\n");

    display_LCD.locate(11, 1);
    display_LCD.printf("Sine\n");

}

void Screens::screen_4(void){

    display_LCD.character(0, 1, 0x20);
    display_LCD.character(10, 1, 0x20);
    display_LCD.character(2, 0, 0x7E);

}

void Screens::screen_5(void){

    display_LCD.character(2, 0, 0x20);
    display_LCD.character(10, 1, 0x20);
    display_LCD.character(0, 1, 0x7E);

}

void Screens::screen_6(void){

    display_LCD.character(2, 0, 0x20);
    display_LCD.character(0, 1, 0x20);
    display_LCD.character(10, 1, 0x7E);

}

void Screens::screen_7(int pulse){

    display_LCD.locate(0, 0);
    display_LCD.printf("Frequency:\n");

    display_LCD.locate(10, 0);
    display_LCD.printf("%d", pulse);

    display_LCD.locate(13, 0);
    display_LCD.printf("Hz\n");

}

void Screens::screen_8(int pulse){

    screen_3();

    switch (pulse) {
    case 0:
        screen_4();
        break;

    case 1:
        screen_5();
        break;

    case 2:
        screen_6();
        break;
     }

}

