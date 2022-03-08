#include "waves.h"
#include "mbed.h"
Waves::Waves() : DAC(DAC_0, DAC_1, DAC_2, DAC_3, DAC_4, DAC_5, DAC_6, DAC_7) {
    
}

void Waves::init() {
  i = 0;
  j = 511;
}

void Waves::clock() {

  flag = true;
  i = i + 1;
  j = j - 1;
}

void Waves::ramp() {
  if (i < 256) {
    DAC = i;
  } else {
    i = 0;
  }
}

void Waves::triangular() {

  if (i < 256) {
    DAC = i;
  }
  if (j < 256) {
    DAC = j;
  }
  if (j < 0) {
    j = 511;
    i = 0;
  }
}

void Waves::sine() {

  if (i < 256) {
    DAC = senoide[i];
  } else {
    i = 0;
  }
}

void Waves::freq_apply(double delay) { clk_func.attach(this, &Waves::clock, delay); }

void Waves::select_wave(int value) {

  switch (value) {
  case 0:
    triangular();
    break;

  case 1:
    ramp();
    break;

  case 2:
    sine();
    break;
  }
}
