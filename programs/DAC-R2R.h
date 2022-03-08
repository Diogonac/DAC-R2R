#include "mbed.h"
#include "all_config.h"
#include <cstdio>


Screens screen;
Waves wave;

InterruptIn confirm_BT(USER_BT); // Declara o botão do usuário para troca de sinal

QEI encoder(PC_5, PC_6, 300);

Timer debouce;

bool aux_deb;

int cont, wave_select;

double delay, start, initialization;

void user_confirm(void); // Rotina para trocar o sinal exibido
void init(void);         // Initialization
void wave_init(void);

void frequency(int pulse, int value); // Rotina para calcular a frequência dado
                                      // o valor do potênciometro

int main() {

  confirm_BT.fall(&user_confirm); // Define quando o botão vai ser detectado
  debouce.start();
  wave.init();

  cont = 0;
  aux_deb = false;
  start = false;
  initialization = false;

  screen.screen_1();

  initialization = true;

  while (1) {

    if (initialization == true && start == true) {

      screen.clean();
      initialization = false;
    }

    switch (cont) {

    case 1:
      screen.screen_2();
      break;

    case 2:
      screen.clean();
      cont = 3;
      break;

    case 3:
      wave_select = encoder.getPulsesLCD();
      screen.screen_8(wave_select);
      break;

    case 4:
      screen.clean();
      cont = 5;

    case 5:
      if (wave_select == 0) {
        frequency(encoder.getPulses(), 2);
      } else {
        frequency(encoder.getPulses(), 1);
      }
      break;

    case 7:
      wave.select_wave(wave_select);
      break;

    case 8:
      screen.clean();
      cont = 3;
    }
  }
}

void user_confirm() {

  if (debouce.read_us() > 2000.0) {
    debouce.stop();

    cont++;
    aux_deb = !aux_deb;
    start = true;

    debouce.reset();
    debouce.start();
  }
}

void frequency(int pulse, int value) {

  screen.screen_7(pulse);

  if (cont == 6) {
    delay = 1.0 / (256 * pulse * value);
    wave.freq_apply(delay);
    cont = 7;
  }
}