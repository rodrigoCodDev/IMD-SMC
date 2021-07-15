// PIC18F45K20

#pragma config FOSC = INTIO67   // Oscilador
#pragma config BOREN = OFF      // Resetar o microcontrolador quando houver queda de tens�o.
#pragma config PBADEN = OFF     // Desligando conversor AC/DC de PORTB

#include <xc.h>
#define _XTAL_FREQ 1000000

void main(void) {
    // Configurando sa�da no PORTD
    TRISD = 0b00000000; 
    PORTD = 0b00000011;
    
    // Configurando entrada com interrup��o
    TRISB = 0b00000001;         // Configura o bit RB0 como entrada.
    INTCONbits.INT0IE = 1;      // Habilitar interrup��o externa INT0
    INTCONbits.INT0IF = 0;      // Limpar flag da interrup��o INT0
    INTCON2bits.INTEDG0 = 0;    // Habilitar interrup��o INT0 na borda de descida
    RCONbits.IPEN = 0;          // Desligar todas as prioridades interrup��o
    INTCONbits.GIE = 1;         // Habilitar interrup��o geral.     
    
    while(1) {
        __delay_ms(70);
        PORTD = (PORTD << 1);
        
        if(PORTD == 0b10000000) {
            PORTD = 0b10000001;
        }
        
        if(PORTD == 0b00000010) {
            PORTD = 0b00000011;
        }
    }
    
    return;
}


void __interrupt() funcao(){  
    
    if (INTCONbits.INT0IF == 1) {
        INTCONbits.INT0IF = 0;
        
        if(PORTD == 0b00011000) {
            // Se a sequ�ncia selecionada foi correta, fa�a...
            int tempo = 0;
            
            // Pisque todos os LEDs PORTD durante 2 segundos
            while(tempo < 2000) {
                PORTD = 0b00000000;
                __delay_ms(50);
                
                PORTD = 0b11111111;
                __delay_ms(50);
                
                tempo += 100;
            }
            
            // Reconfigure a sa�da, reinicializando o jogo
            PORTD = 0b00000011;
        }
    }
}