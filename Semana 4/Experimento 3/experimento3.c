// PIC18F4520 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = INTIO67    // Oscillator Selection bits (HS oscillator)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <xc.h>
#define _XTAL_FREQ 1000000

// Definindo variáveis das saídas para as LEDs
#define verde1 PORTDbits.RD0
#define amarelo1 PORTDbits.RD1
#define vermelho1 PORTDbits.RD2

#define verde2 PORTDbits.RD5
#define amarelo2 PORTDbits.RD6
#define vermelho2 PORTDbits.RD7

unsigned int toques = 0;

void parar();

void main(void) {
    TRISD = 0b00000000;      // Configura os bits RD como saída.
    
    TRISB = 0b00000001;      // Configura o bit RB0 como entrada.
    INTCONbits.INT0IE = 1;   // Habilitar interrupção externa INT0
    INTCONbits.INT0IF = 0;   // Limpar flag da interrupção INT0
    INTCON2bits.INTEDG0 = 0; // Habilitar interrupção INT0 na borda de descida
    RCONbits.IPEN = 0;       // Desligar todas as prioridades interrupção
    INTCONbits.GIE = 1;      // Habilitar interrupção geral.
    
    while(1){
        // a. LEDs acesos por 3 segundos: Verde1 (DS0) e Vermelho2 (DS7);
        verde1 = 1;
        vermelho2 = 1;
        __delay_ms(3000);
        verde1 = 0;
        
        // b. LEDs acesos por 1 segundo: Amarelo1 (DS1) e Vermelho2 (DS7);
        amarelo1 = 1;
        vermelho2 = 1;
        __delay_ms(1000);
        amarelo1 = 0;
        vermelho2 = 0;
        
        // c. LEDs acesos por 3 segundos: Vermelho1 (DS2) e Verde2 (DS5);
        vermelho1 = 1;
        verde2 = 1;
        __delay_ms(3000);
        verde2 = 0;
        
        // d. LEDs acesos por 1 segundo: Vermelho1 (DS2) e Amarelo2 (DS6);
        vermelho1 = 1;
        amarelo2 = 1;
        __delay_ms(1000);
        amarelo2 = 0;
        vermelho1 = 0;
    }
    
    return;
}

void __interrupt() funcao(){
    
    if (INTCONbits.INT0IF == 1) {
        INTCONbits.INT0IF = 0;
        
        toques++;
        
        if (toques == 3) {
            parar();
            toques = 0;
        }
    }
    
}

void parar() {
    int estadoParada = PORTD;
    
    // Acende os LEDs vermelhos para parar o tráfego de veículos
    verde1 = 0;
    amarelo1 = 0;
    
    verde2 = 0;
    amarelo2 = 0;
    
    vermelho1 = 1;
    vermelho2 = 1;
    
    __delay_ms(2000);
    
    vermelho1 = 0;
    vermelho2 = 0;
    
    PORTD = estadoParada;
}
