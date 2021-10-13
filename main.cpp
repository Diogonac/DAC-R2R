#include "mbed.h"

Serial pc(D1, D0); // Comunicação com USB

// BusOut saida(D4, D5, D6, D7, D8, D9, D10, D11); //Barramento dos bits do DAC
// R-2R
BusOut saida(D9, D8, D7, D6, D5, D4, D3, D2); // Barramento dos bits do DAC R-2R

InterruptIn troca_onda(PC_13); // Declara o botão do usuário para troca de sinal

DigitalOut teste_pisca(D12);

int senoide[] = {
0x80,0x83,0x86,0x89,0x8c,0x8f,0x92,0x95,
0x98,0x9b,0x9e,0xa2,0xa5,0xa7,0xaa,0xad,
0xb0,0xb3,0xb6,0xb9,0xbc,0xbe,0xc1,0xc4,
0xc6,0xc9,0xcb,0xce,0xd0,0xd3,0xd5,0xd7,
0xda,0xdc,0xde,0xe0,0xe2,0xe4,0xe6,0xe8,
0xea,0xeb,0xed,0xee,0xf0,0xf1,0xf3,0xf4,
0xf5,0xf6,0xf8,0xf9,0xfa,0xfa,0xfb,0xfc,
0xfd,0xfd,0xfe,0xfe,0xfe,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xfe,0xfe,0xfe,0xfd,
0xfd,0xfc,0xfb,0xfa,0xfa,0xf9,0xf8,0xf6,
0xf5,0xf4,0xf3,0xf1,0xf0,0xee,0xed,0xeb,
0xea,0xe8,0xe6,0xe4,0xe2,0xe0,0xde,0xdc,
0xda,0xd7,0xd5,0xd3,0xd0,0xce,0xcb,0xc9,
0xc6,0xc4,0xc1,0xbe,0xbc,0xb9,0xb6,0xb3,
0xb0,0xad,0xaa,0xa7,0xa5,0xa2,0x9e,0x9b,
0x98,0x95,0x92,0x8f,0x8c,0x89,0x86,0x83,
0x80,0x7c,0x79,0x76,0x73,0x70,0x6d,0x6a,
0x67,0x64,0x61,0x5d,0x5a,0x58,0x55,0x52,
0x4f,0x4c,0x49,0x46,0x43,0x41,0x3e,0x3b,
0x39,0x36,0x34,0x31,0x2f,0x2c,0x2a,0x28,
0x25,0x23,0x21,0x1f,0x1d,0x1b,0x19,0x17,
0x15,0x14,0x12,0x11,0xf,0xe,0xc,0xb,
0xa,0x9,0x7,0x6,0x5,0x5,0x4,0x3,
0x2,0x2,0x1,0x1,0x1,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x2,
0x2,0x3,0x4,0x5,0x5,0x6,0x7,0x9,
0xa,0xb,0xc,0xe,0xf,0x11,0x12,0x14,
0x15,0x17,0x19,0x1b,0x1d,0x1f,0x21,0x23,
0x25,0x28,0x2a,0x2c,0x2f,0x31,0x34,0x36,
0x39,0x3b,0x3e,0x41,0x43,0x46,0x49,0x4c,
0x4f,0x52,0x55,0x58,0x5a,0x5d,0x61,0x64,
0x67,0x6a,0x6d,0x70,0x73,0x76,0x79,0x7c,
}; // Look Up table para gerar um sinal senoidal

int i, cont;

void rotina_troca_onda(void); // Rotina para trocar o sinal exibido

void rotina_rampa(void);      // Rotina para gerar um sinal de uma rampa
void rotina_triangular(void); // Rotina para gerar um sinal triangular
void rotina_senoidal(void);   // Rotina para gerar um sinal de uma senoide
void rotina_PWM(void);        // Rotina para gerar um sinal de uma senoide

int main() {
  pc.baud(115200); // Define a velocidade da porta USB

  troca_onda.fall(&rotina_troca_onda); // Define quando o botão vai ser
                                       // detectado

  while (1) {

    if (cont == 0)
      rotina_rampa();
    if (cont == 1)
      rotina_triangular();
    if (cont == 2)
      rotina_senoidal();
    if (cont == 3)
      rotina_PWM();
    if (cont >= 4)
      cont = 0;
  }
}

void rotina_troca_onda() { cont++; }

void rotina_rampa() {
  for (i = 0; i <= 255; i++) {
    saida = i;
    wait(0.01);
  }
}

void rotina_triangular() {
  for (i = 0; i <= 255; i++) {
    saida = i;
    wait(0.001);
  }

  for (i = 255; i > -1; i--) {
    saida = i;
    wait(0.001);
  }
}

void rotina_senoidal() {
  for (i = 0; i <= 255; i++) {
    saida = senoide[i];
    wait(0.001);
  }
}

void rotina_PWM() {

  teste_pisca = 1;
  wait_ms(20);
  teste_pisca = 0;
  wait_ms(20);
}