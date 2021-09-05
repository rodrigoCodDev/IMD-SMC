# SEMANA 8

**Microcontrolador:** 
- PIC18F45K20

**Objetivos:**
- Programar PIC; e
- Programar entrada analógica.


## Experimento 1

![Experimento 1](./../../image/Semana8/experimento1.gif)

Neste experimento, o PIC foi programado para ler valores analógicos da porta RA0 conectado a um potenciômetro. Os valores lidos na leitura(entre 0 e 1023) são processados e passados para as saídas nas PORTD que possui conexão com LEDs

Os primeiros 7 LEDs (pinos) representam o valor da leitura e o último é configurado para mudar o tempo em que é aceso em relação ao valor e a um tempo padrão estabelecido.