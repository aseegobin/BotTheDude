#include <xc.h>
#pragma config FOSC=INTRCIO, WDTE=OFF, PWRTE=OFF, MCLRE=ON, CP=OFF, CPD=OFF, BOREN=OFF, IESO=OFF, FCMEN=OFF
#define _XTAL_FREQ 4000000

int main()
{
    TRISA = 0xFF; //set all digital I/O to inputs
    TRISB = 0xFF;
    TRISC = 0xFF;

    ANSEL = 0x00; //disable all analog ports
    ANSELH = 0x00;

    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 0;

    ///////////////////////
    // Main Program Loop //
    ///////////////////////

    while(1)
    {
       __delay_ms(5000);
       PORTCbits.RC3 = 1;
       PORTCbits.RC6 = 1;
       PORTCbits.RC7 = 0;
       __delay_ms(3000);
       PORTCbits.RC3 = 1;
       PORTCbits.RC6 = 0;
       PORTCbits.RC7 = 1;
       __delay_ms(5000);
       PORTCbits.RC3 = 1;
       PORTCbits.RC6 = 1;
       PORTCbits.RC7 = 0;
       __delay_ms(3000);
       PORTCbits.RC3 = 0;

    }
    return 0;
}