#include "mbed.h"
#include "all_config.h"


Serial pc(TX, RX); // Comunicação com USB

TextLCD LCD(D8, D9, D4, D5, D6, D7);

// R-2R
BusOut saida(PA_11, PB_12, PB_2, PB_1, PB_15, PB_14, PB_13, PC_4); // Barramento dos bits do DAC R-2R

InterruptIn confirm_BT(USER_BT); // Declara o botão do usuário para troca de sinal

QEI encoder(PC_5, PC_6, 15);

Timer debouce;
Ticker clk_func;
bool flag;

float analog;
bool aux_deb;

int i, cont, j;
double tempo, espera, start, initialization;

double freq[60] = {5,   10,  15,  20,  25,  30,  35,  40,  45,  50,  55,  60,
                   65,  70,  75,  80,  85,  90,  95,  100, 105, 110, 115, 120,
                   125, 130, 135, 140, 145, 150, 155, 160, 165, 170, 175, 180,
                   185, 190, 195, 200, 205, 210, 215, 220, 225, 230, 235, 240,
                   245, 250, 255, 260, 265, 270, 275, 280, 285, 290, 295, 300};

int periodos[60] = {

};

char underline[8] =
{
0b00000,
0b00000,
0b00000 ,
0b00000,
0b00000,
0b00000,
0b00000,
0b11111
};

void user_confirm(void); // Rotina para trocar o sinal exibido
void init(void); // Initialization 
void wave_init(void);
void wave_selection_1(void);
void slider(void);

void clock_func(void);
void rotina_rampa(void);           // Rotina para gerar um sinal de uma rampa
void rotina_triangular(void);      // Rotina para gerar um sinal triangular
void rotina_senoidal(void);        // Rotina para gerar um sinal de uma senoide
void rotina_frequencia(int pulse); // Rotina para calcular a frequência dado o
                                   // valor do potênciometro

 int main() {
  pc.baud(115200); // Define a velocidade da porta USB

  confirm_BT.fall(&user_confirm); // Define quando o botão vai ser detectado

  clk_func.attach(&clock_func, 0.390625e-4);

  debouce.start();

  init();

  while (1) {


    /* Read encoder to calculate delay time */
    rotina_frequencia(encoder.getPulsesLCD());

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
        // cont = 4;
        break;
    
    case 4:
        slider();
        break;





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
    LCD.locate(7, 1);
    LCD.printf("OK\n");
    LCD.character(15, 1, 0x7E);

    // if(encoder.getPulsesLCD() <= 15 && encoder.getPulsesLCD() >= 0){
    LCD.character(encoder.getPulsesLCD(), 1, 0x5F);
    LCD.character(encoder.getPulsesLCD()-1, 1, 0x20);
    LCD.character(encoder.getPulsesLCD()+1, 1, 0x20);
// }

// if(encoder.getPulses() > 16){
//     LCD.character(15, 1, 0x5F);
// }

// if(encoder.getPulses() < 0){
//     LCD.character(0, 1, 0x5F);
// }
}
void slider(){
    LCD.character(encoder.getPulses(), 1, 0x5F);
    LCD.character(encoder.getPulses()-1, 1, 0x20);
    LCD.character(encoder.getPulses()+1, 1, 0x20);
    //pc.printf("Pulses= %d\r\n", encoder.getPulsesLCD());

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

void rotina_frequencia(int pulse) {
//   if (pulse <= 59 && pulse > 0) {
//     espera = ((1 / (freq[pulse] * 256)));

//   }

//   else {

//     espera = ((1 / (freq[0] * 256)));
//   }
printf("Pulsos: %d\r\n", pulse);
}