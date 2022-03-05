# **DAC-R2R**

## **O que é um DAC-R2R?**
*Digital-Analog Converter* é todo aquele circuito capaz de transformar um determinado sinal discreto em um sinal analógico ou contínuo. Estes circuitos são fundamentais quando queremos entender o comportamento de um sistema, cujo sinal de entrada seja uma senoide com amplitude e frequência definidas. Em outras palavras, o Conversor Digital-Analógico é a parte principal de um gerador de sinais. 

Neste trabalho foi utilizada a topologia R-2R de 8-bit, pois ela utiliza apenas resistores para realizar a conversão de digital para analógico. 

## Como construir um DAC-R2R?
A figura abaixo ilustra como é a construção do DAC de 8-bit, neste projeto foram utilizados apenas resistores de 10kOhm de precisão. O seu funcionamento é muito simples, basta criar uma sequência de pulsos com sinal lógico alto (1) ou baixo (0) nos pinos (PA11, PB12 ...), para poder obter um sinal de tensão contínuo no tempo (DAC_OUT_LOW). 

![](https://github.com/Diogonac/DAC-R2R/blob/main/images/DAC.png)
## Contas de resolução 
Cada pino de entrada equivale a 1-bit do DAC, cada bit pode corresponder a dois valores lógicos, alto ou baixo, ou seja, temos duas possibilidades de informações para o DAC por bit. Como temos 8-bit, teremos 2^8 - 1 possibilidades de informações. Agora imagine que cada informação corresponde a um degrau de uma escada. Mas o que significa essa informação? Cada degrau da escada equivale a um nível específico de tensão na saída do DAC (DAC_OUT_LOW). Dessa forma, o nível específico de tensão foi convertido em um sinal analógico. 

![](https://github.com/Diogonac/DAC-R2R/blob/main/images/MAT.svg)

## Amplificando o sinal de saída
Com o objetivo de permitir que o DAC desenvolvido neste projeto possa ser usado como um gerador de sinais em outros trabalhos, foi implementado um circuito amplificador não inversor com ajuste de tensão por meio de um *trimpot*, conforme o esquemático abaixo.



### Implementação de potênciometro para ajustes da frequência
### Descrição das telas da IHM

## Comparação da simulação e do real para os três tipos de onda 
### Rampa
### Triangular
### Senoidal 
