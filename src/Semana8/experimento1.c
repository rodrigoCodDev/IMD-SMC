// PIC18F45K20

#pragma config FOSC = INTIO67   // Oscilador
#pragma config BOREN = OFF      // Resetar o microcontrolador quando houver queda de tens�o.
#pragma config WDTEN = OFF      // Watchdog desligado

#include <xc.h>
#define _XTAL_FREQ 4000000
#define TEMPO_PADRAO 1000

unsigned int leitura = 0;           // Leitura atual da entrada 
unsigned int leituraPassada = 0;    // Leitura anterior da entrada

unsigned int tempoAceso = 10;    // O tempo em que o LED ficar� aceso
float porcentagem = 0; // Porcentagem de tempo padr�o que o LED ficar� aceso

void delay_ms();

void main(void) {
    
    //Configurando entrada anal�gica
    OSCCONbits.IRCF = 0b110; // Configurar oscilador interno para 4MHz
    ADCON2bits.ADCS = 0b110; // Clock: Fosc/64
    ADCON2bits.ACQT = 0b101; // Tempo de aquisi��o: 12*TAD
    ADCON2bits.ADFM = 1; // Formato do valor digital justificado � direita.
    ADCON1 = 0b00000000; // ADC Vref = Vdd,Vss
    ANSEL = 0b00000001; // Configura RA0 como anal�gica
    TRISA = 0b00000001; // Configura RA0 como entrada
    ADCON0bits.CHS = 0b0000; // Configura canal AN0 (RA0)
    ADCON0bits.ADON = 1; // Habilitar conversor AD
    
    // Configura todos os pinos D como sa�da
    TRISD = 0b00000000;
    
    while (1) {
        ADCON0bits.GO = 1; // Inicia a convers�o de anal�gico para digital
        
        while ( !ADCON0bits.GO_DONE ) {
            // Aguarda fim da convers�o
        }
        
        // Se o coversor AD for de 10 bits
        // ADRESH -> Parte mais significativa dos bits recebidos (8 bits)
        // ADRESL -> Parte menos significativa dos bits recebidos (2 bits)
        leitura = (ADRESH << 8); // Deslocamento de 8 bits da entrada ADRESH
        leitura = leitura + ADRESL;
        
        if (leitura != leituraPassada) {
            PORTD = leitura;
            
            // Gera um valor proporcional na faixa de 0 a 1
            porcentagem = ((float) leitura/1023);
            
            // Calcula tempo em que o LED passa aceso pela porcentagem
            tempoAceso = TEMPO_PADRAO * porcentagem;
        }
        
        PORTDbits.RD7 = 1;
        delay_ms(tempoAceso);
        
        PORTDbits.RD7 = 0;
        delay_ms(TEMPO_PADRAO);
        
        leituraPassada = leitura;
    }
    
    return;
}

void delay_ms(int ms) {
    while (ms--) {
        __delay_us(1000);  // one millisecond
    }
}