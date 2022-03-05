#include "mbed.h"
#include "all_config.h"
#include <cstdio>


Serial pc(TX, RX); // Comunicação com USB

TextLCD LCD(D8, D9, D4, D5, D6, D7);

// R-2R
BusOut saida(PA_11, PB_12, PB_2, PB_1, PB_15, PB_14, PB_13, PC_4); // Barramento dos bits do DAC R-2R

InterruptIn confirm_BT(USER_BT); // Declara o botão do usuário para troca de sinal

QEI encoder(PC_5, PC_6, 300);

Timer debouce;
Ticker clk_func;
bool flag;

float analog;
bool aux_deb;

int i, cont, j, wave_select;;
double tempo, espera, start, initialization;



void user_confirm(void); // Rotina para trocar o sinal exibido
void init(void); // Initialization 
void wave_init(void);
void wave_selection_1(void);
void slider(void);

void clock_func(void);
void rotina_rampa(void);           // Rotina para gerar um sinal de uma rampa
void rotina_triangular(void);      // Rotina para gerar um sinal triangular
void rotina_senoidal(void);        // Rotina para gerar um sinal de uma senoide
void frequency(int pulse, int value); // Rotina para calcular a frequência dado o
                                   // valor do potênciometro

 int main() {
  pc.baud(115200); // Define a velocidade da porta USB

  confirm_BT.fall(&user_confirm); // Define quando o botão vai ser detectado

  

  debouce.start();

  init();

  while (1) {


    /* Read encoder to calculate delay time */
    //pc.printf("Pulses: %d\r\n", encoder.getPulsesLCD());

    if (initialization == true && start == true) {

        LCD.cls();
        initialization = false;
    
    }

    switch (cont) {

    case 1:
        wave_init();
        break;
    
    case 2:
        LCD.cls();
        cont = 3;
        break;
    
    case 3:
        wave_selection_1();
        break;
    
    case 4:
        LCD.cls();
        cont = 5;

    case 5:
        if(wave_select == 0){frequency(encoder.getPulses(), 2);}
        else{frequency(encoder.getPulses(), 1);}
        break;

    case 7:
            switch (wave_select) {
                case 0:
                    rotina_triangular();
                    break;

                case 1:
                    rotina_rampa();
                    break;

                case 2:
                    rotina_senoidal();
                    break;
                }
        break;
    
    case 8:
        LCD.cls();
        cont = 3;


    }

    // if (cont == 0)
    //   rotina_rampa();
    // if (cont == 1)
    //   rotina_triangular();
    // if (cont == 2)
    //   rotina_senoidal();
    // if (cont >= 3)
    //   cont = 0;
  }
  

}

void wave_init(){

    LCD.locate(0, 0);
    LCD.printf("Press to select\n");
    LCD.locate(0, 1);
    LCD.printf("the desired wave\n");

}

void wave_selection_1(){
    
    LCD.locate(3, 0);
    LCD.printf("Triangular\n");

    LCD.locate(1, 1);
    LCD.printf("Ramp\n");

    LCD.locate(11, 1);
    LCD.printf("Sine\n");

    switch (encoder.getPulsesLCD()) {
    case 0:
        LCD.character(0, 1, 0x20);
        LCD.character(10, 1, 0x20);
        LCD.character(2, 0, 0x7E);
        break;

    case 1:
        LCD.character(2, 0, 0x20);
        LCD.character(10, 1, 0x20);
        LCD.character(0, 1, 0x7E);
        break;

    case 2:
        LCD.character(2, 0, 0x20);
        LCD.character(0, 1, 0x20);
        LCD.character(10, 1, 0x7E);
        break;
     }

     wave_select = encoder.getPulsesLCD();
}

void init(){

  i = 0;
  j = 511;
  cont = 0;
  aux_deb = false;
  start = false;
  initialization = false;

  LCD.locate(5, 0);
  LCD.printf("Hello!\n");
  LCD.locate(1, 1);
  LCD.printf("Press to start\n");

  initialization = true;
}

void user_confirm() { 

    if(debouce.read_us() > 2000.0){
        debouce.stop();

        cont++;
        aux_deb =! aux_deb;
        start = true;

        debouce.reset();
        debouce.start();

    }


     
    }



void clock_func() {
  flag = true;
  i = i + 1;
  j = j - 1;
}

void rotina_rampa() {
  if (i < 256) {
    saida = i;
  } else {
    i = 0;
  }
}

void rotina_triangular() {

  if (i < 256) {
    saida = i;
  }
  if (j < 256 ) {
    saida = j;
  }
  if(j < 0){
      j = 511;
      i = 0;
  }
}

void rotina_senoidal() {

  if (i < 256) {
    saida = senoide[i];
  } else {
    i = 0;
  }
}

void frequency(int pulse, int value) {

    LCD.locate(0, 0);
    LCD.printf("Frequency:\n");

    LCD.locate(10, 0);
    LCD.printf("%d", pulse);

    LCD.locate(13, 0);
    LCD.printf("Hz\n");

    if(cont == 6){
        espera = 1.0/(256*pulse*value);
        clk_func.attach(&clock_func, espera);
        cont = 7;
    }
    
}