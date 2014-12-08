#include <xc.h>
#pragma config FOSC=INTRCIO, WDTE=OFF, PWRTE=OFF, MCLRE=ON, CP=OFF, CPD=OFF, BOREN=OFF, IESO=OFF, FCMEN=OFF
#define _XTAL_FREQ 4000000

int main()
{
    int result1, result2; //variables to store our ADC result

    TRISA = 0xFF; //set all digital I/O to inputs
    TRISB = 0xFF;
    TRISC = 0xFF;

    ANSEL = 0x00; //disable all analog ports
    ANSELH = 0x00;

    TRISAbits.TRISA2 = 1; //Disable the output driver for pin RA2/AN2
    ANSELbits.ANS2 = 1; //set RA2/AN2 to analog mode

    TRISAbits.TRISA0 = 1; //Disable the output driver for pin RA0/AN0
    ANSELbits.ANS0 = 1; //set RA0/AN0 to analog mode

    TRISCbits.TRISC0 = 0; //set RC0 as an output
    TRISCbits.TRISC1 = 0;

    ///////////////
    // ADC Setup //
    ///////////////

    ADCON0bits.ADFM = 1; //ADC result is right justified
    ADCON0bits.VCFG = 0; //Vdd is the +ve reference
    ADCON1bits.ADCS = 0b001; //Fosc/8 is the conversion clock
                            //This is selected because the conversion
                            //clock period (Tad) must be greater than 1.5us.
                            //With a Fosc of 4MHz, Fosc/8 results in a Tad
                            //of 2us.
    ADCON0bits.ADON = 1; //Turn on the ADC

    ///////////////////////
    // Main Program Loop //
    ///////////////////////

    while(1)
    {
        __delay_us(5); //Wait the acquisition time (about 5us).

        ADCON0bits.CHS = 0; //select analog input, AN2
        
        ADCON0bits.GO = 1; //start the conversion
        while(ADCON0bits.GO==1){}; //wait for the conversion to end
        result1 = (ADRESH<<8)|ADRESL; //combine the 10 bits of the conversion
        
        __delay_us(5); //Wait the acquisition time (about 5us).
        ADCON0bits.CHS = 2; //select analog input, AN5

        ADCON0bits.GO = 1; //start the conversion
        while(ADCON0bits.GO==1){}; //wait for the conversion to end
        result2 = (ADRESH<<8)|ADRESL; //combine the 10 bits of the conversion
        
        if(result1 > 170)
        {
            m0for();
        }
        else if (result1 < 110 )
        {
            m0rev();
        }
        else
        {
            PORTCbits.RC0 = 0;
        }

        if(result2 > 170)
        {
            m1rev();
        }
        else if (result2 < 110)
        {
            m1for();
        }
        else
        {
            PORTCbits.RC1 = 0;
        }
    }
    return 0;
}

int m0for()
{
    PORTCbits.RC0 = 1;
    __delay_ms(1);
    PORTCbits.RC0 = 0;
    __delay_ms(19);
}

int m0rev()
{
    PORTCbits.RC0 = 1;
    __delay_ms(10);
    PORTCbits.RC0 = 0;
    __delay_ms(10);
}

int m1for()
{
    PORTCbits.RC1 = 1;
    __delay_ms(1);
    PORTCbits.RC1 = 0;
    __delay_ms(19);
}

int m1rev()
{
    PORTCbits.RC1 = 1;
    __delay_ms(10);
    PORTCbits.RC1 = 0;
    __delay_ms(10);
}
