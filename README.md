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

![](https://github.com/Diogonac/DAC-R2R/blob/main/images/AMP.png)

É importante salientar que, as conexões TRIN1 e TRIN2 se referem aos pinos do *trimpot* de 10kOhm e o capacitor C4 foi utilizado para filtrar o sinal de saída do DAC. Logo com esse arranjo do amplificador o sinal DAC_OUT_LOW pode ser amplificado em até x10, porém, a tensão de saída DAC_OUT_HIGH é limitada pela tensão de alimentação do amplificador operacional utilizado (LM358N).

## Implementação do encoder rotativo 
Para facilitar a interação do DAC com o usuário, foi utilizado apenas 1 componente, o econder rotativo. Este componente possui três sinais de saída: Botão 0/1 (SW_raw), Clock horário (DT_raw) e Clock anti-horário (CLK_raw). Com essas informação, foi possível desenvolver lógicas que simplifiquem o uso do dispositivo.

Os sinais de saída desse encoder são muito ruidosos, ocasionando leituras falsas ao longo do desenvolvimento desse projeto. Para corrigir esse problema nos sinais, foi utilizado um schmitt-trigger (SN74HC14N), conforme a imagem a seguir. 

![](https://github.com/Diogonac/DAC-R2R/blob/main/images/SCT.png)

## Descrição das telas da IHM
Para conceber a interface com o usuário, foi utilizado uma *shield* de um LCD 2x16. Para poder trocar de tela ou confirmar um parâmetro, basta dar um *click* no econder. Por outro lado, para alterar algum parâmetro/seleção, basta girar o encoder em qualquer sentido. A seguir, estão ilustradas as possíveis telas da IHM. 

![](https://github.com/Diogonac/DAC-R2R/blob/main/images/T1.jpg)
![](https://github.com/Diogonac/DAC-R2R/blob/main/images/T2.jpg)
![](https://github.com/Diogonac/DAC-R2R/blob/main/images/T3.jpg)
![](https://github.com/Diogonac/DAC-R2R/blob/main/images/T4.jpg)

## Placa de Circuito Impressa (PCI)
Para poder compactar o projeto e evitar ruídos de *protoboard*, foi desenvolvido uma *shield* para agrupar todos os componentes. A seguir estão algumas fotos do resultado.

![](https://github.com/Diogonac/DAC-R2R/blob/main/images/PCB1.jpg)
![](https://github.com/Diogonac/DAC-R2R/blob/main/images/PCB2.jpg)
![](https://github.com/Diogonac/DAC-R2R/blob/main/images/PCB3.jpg)
![](https://github.com/Diogonac/DAC-R2R/blob/main/images/PCB4.jpg)
Caso você queira melhorar ou replicar este projeto, os arquivos estão na pasta "proteus".

Descrição das conexões da *shield*.
![](https://github.com/Diogonac/DAC-R2R/blob/main/images/PW.svg)


## Resultados
### Rampa
### Triangular
### Senoidal 
