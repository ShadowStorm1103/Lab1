// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

unsigned char racer1;
unsigned char racer2;
int n; 
int jg;
void carrera (void);
void delay_ms (unsigned int dms);
void db (void);
//void db2 (void);
void set (void);
void mario (void);
void MR (void);
void MV (void);
void winner1 (void);
void MRS (void);
void MVS (void);
void winner2 (void); 
void carrerauno (void);

void main(void) {
    set();
    AQUI:
//    MR();
    db();
    carrerauno();
    n=0;
    goto AQUI;
    return;
}

void carrera(void){
    PORTDbits.RD3 = 1;
    PORTDbits.RD2 = 1;
    PORTDbits.RD1 = 1;
    PORTC = 0xB6;
    delay_ms(500);
    
    PORTDbits.RD3 = 0;
    PORTDbits.RD2 = 1;
    PORTDbits.RD1 = 1;
    PORTC = 0xB3;
    delay_ms(500);
    
    PORTDbits.RD3 = 0;
    PORTDbits.RD2 = 0;
    PORTDbits.RD1 = 1;
    PORTC = 0x14;
    delay_ms(500);
    
    PORTDbits.RD3 = 0;
    PORTDbits.RD2 = 0;
    PORTDbits.RD1 = 0;
    PORTC = 0x77;
    delay_ms(500);
}

void delay_ms(unsigned int dms){
    for(int i = 0; i<dms; i++){
        for(int j = 0; j<255; j++);
    }
}

void db (void){
    while (n == 0){
        if (PORTDbits.RD7 == 1){
            n = 0;
        }
        else {
            n = 1;
            jg = 1;
        }
    }
    //carrerauno();
    //mario();
//    db2();
}

void db2 (void){
    while (n == 1){
        if (PORTDbits.RD7 == 0){
            n = 1;
        }
        else {
            n = 0x00;
            jg = 0x01;
        }
    }
}

void set (void){
    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0xE0;
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTAbits.RA7 = 0;
    PORTDbits.RD0 = 0;
    PORTDbits.RD4 = 0;
    racer1 = 0;
    racer2 = 0;
    n = 0;
    jg = 1;
}

void mario (void){
    while (jg == 1){
        if (PORTDbits.RD6 == 0){
            MR();
        }
        else if (PORTDbits.RD5 == 0){
            MV();
        }
        else {
            return;
        }
    }
}

void MR(void){
    if (PORTDbits.RD6 == 1){
        if (racer1 == 0){
            racer1 = 1;
            racer1 = PORTA;
        }
        else if (0<racer1 && racer1< 128){
            racer1 = racer1 * 2;
            PORTA = racer1;
        }
        else if (racer1 == 128){
            winner1();
        }
        else {   
        }
    }
    else if (PORTDbits.RD5 == 0){
        MVS();
    }
    else {
    }
    
}

void MV(void){
    if (PORTDbits.RD5 == 1){
        if (racer2 == 0){
            racer2 = 1;
            racer2 = PORTB;
        }
        else if (0<racer2 && racer2 < 128){
            racer2 = racer2 * 2;
            PORTB = racer2;
        }
        else if (racer2 == 128){
            winner2();
        }
        else {   
        }
    }
    else if (PORTDbits.RD6 == 0){
        MRS();
    }
    else {
    }
}

void MVS (void){
    if (PORTDbits.RD5){
        if (racer2 == 0){
            racer2 = 1;
            racer2 = PORTB;
        }
        else if (0<racer2 && racer2< 128){
            racer2 = racer2 * 2;
            PORTB = racer2;
        }
        else if (racer2 == 128){
            winner2();
        }
        else {   
        }
    }
}

void MRS (void){
    if (PORTDbits.RD6 == 1){
        if (racer1 == 0){
            racer1 = 1;
            racer1 = PORTA;
        }
        else if (0<racer1 && racer1< 128){
            racer1 = racer1 * 2;
            PORTA = racer1;
        }
        else if (racer1 == 128){
            winner1();
        }
        else {   
        }
    }
}

void winner1 (void){
    PORTA = 0x00;
    jg = 0; 
    PORTDbits.RD0 = 1;
    PORTC = 0x14;
}

void winner2 (void){
    PORTB = 0x00;
    jg = 0; 
    PORTDbits.RD4 = 1;
    PORTC = 0xB3;
}

void carrerauno (void){
    if (PORTDbits.RD7 == 0){
        carrera();
    }
}