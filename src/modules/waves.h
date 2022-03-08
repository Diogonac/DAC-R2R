#ifndef waves_h
#define waves_h

#include "mbed.h"
#include "all_config.h"

// Classe Actuators
class Waves

{

public:

    // Construtor da classe
    Waves();

    // Initialization counters
    void init(void);

    // Waves
    void clock(void);
    void ramp(void);
    void sine(void);
    void triangular(void);
    void freq_apply(double delay);
    void select_wave(int value);

    BusOut DAC;

    // Counters
    int i, j;

    Ticker clk_func;
    bool flag;

private:

};

#endif