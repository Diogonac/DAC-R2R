#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include "mbed.h"


#define PREV_MASK 0x1 //Mask for the previous state in determining direction
//of rotation.
#define CURR_MASK 0x2 //Mask for the current state in determining direction
//of rotation.
#define INVALID   0x3 //XORing two states where both bits have changed.

class QEI
{

public:
    QEI(PinName channelA, PinName channelB, int pulsesPerRev);
    void set(int pul, int rev);
    void reset(void);

    int getPulses(void);
    int getPulsesLCD(void);
    int getRev_d();

    double getRev_f();
    double getAngle();
    double getSumangle();
    double getRPM();
    int          pulsesPerRev_;
private:
    Timer Mper;
    double RPM;
    void encode(void);

    InterruptIn channelA_;
    InterruptIn channelB_;
    int          round_rev_d;
    int          prevState_, currState_;
    
    double angle_, sumangle, round_rev_f;
    int angle_pulses;
    volatile int pulses_, lcdPulses_;
    volatile int revolutions_;
};

#endif
