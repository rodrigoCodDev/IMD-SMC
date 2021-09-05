// PIC18F45K20

#pragma config FOSC = INTIO67   // Oscilador
#pragma config BOREN = OFF      // Resetar o microcontrolador quando houver queda de tens�o.
#pragma config PBADEN = OFF     // Desligando conversor AC/DC de PORTB

#include <xc.h>
#define _XTAL_FREQ 4000000

void main(void) {
    // Configurando sa�da no PORTD
    TRISD = 0b00000000;
    PORTD = 0b00000000;
    
    // Cofigura��o para entrada de RB0 com interrupcao
    TRISB = 0b00000001;        // Configurar o bit RB0 como entrada.
    
    INTCONbits.INT0IE = 1;      // Habilitar interrup��o externa INT0
    INTCONbits.INT0IF = 0;      // Limpar flag da interrup��o INT0
    INTCON2bits.INTEDG0 = 0;	// Habilitar interrup��o INT0 na borda de descida
    RCONbits.IPEN = 0;          // Desligar todas as prioridades na interrup��o.
    
    
    // Configura��o do timer
    OSCCONbits.IRCF = 0b101; // Oscilador interno 4MHz
    
    T0CONbits.TMR0ON = 0;   // Parar o contador TIMER0
    T0CONbits.T08BIT = 0;   // Selecionar o modo 16-bits
    T0CONbits.T0CS = 0;     // Selecionar o clock interno
    T0CONbits.PSA = 0;      // Selecionar o prescaler
    T0CONbits.T0PS = 0;     // Prescaler: dividir 1:2
    INTCONbits.TMR0IE = 1;  // Habilitar o TIMER0
    INTCONbits.TMR0IF = 0;  // Limpar a flag do TIMER0
    T0CONbits.TMR0ON = 1;   // Iniciar o TIMER0

    INTCONbits.GIE = 1;     // Habilitar a interrup��o geral
    INTCONbits.PEIE = 1;    // Habilitar a interrup��o de periferica; TIMER0 = Perif�rico.

    while(1) {
        
    }
    
    return;
}

void __interrupt() interrupcao(){
    
    if (INTCONbits.INT0IF == 1) {
        INTCONbits.INT0IF = 0; // Limpar a flag para detectar uma nova interrup��o
        
        __delay_ms(3000);
        PORTD = 0b00000001;
        __delay_ms(2000);
        
        int tempo = 0;
        
        do {
            PORTD = 0b00000100;
            __delay_ms(100);
            
            PORTD = 0b00000000;
            __delay_ms(100);
            
            tempo += 200;
        } while (tempo < 2000);
        
        
        tempo = 0;
        PORTD = 0b00010000;
        int sentido = 1;
        
        do {
            if (sentido == 1) {
                // Se sentido for 1, desloque para esquerda
                PORTD = PORTD << 1;
                
                if (PORTD == 0b00000000) {
                    PORTD = 0b01000000;
                    sentido = 0;
                }
                
                __delay_ms(600);
                
            } else {
                // Se sentido for 0, desloque para direita
                PORTD = PORTD >> 1;
                
                if (PORTD == 0b00001000) {
                    PORTD = 0b00100000;
                    sentido = 1;
                }
                
                __delay_ms(600);
            }
            
            tempo += 600;
        } while (tempo < 20000);
       
        PORTD = 0b00000000;
    }
    
    if (INTCONbits.TMR0IF == 1){
        INTCONbits.TMR0IF = 0;     // Limpar a flag 
    }
}
