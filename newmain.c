// PIC32MX360F512L Configuration Bit Settings
 
// 'C' source line config statements
 
// DEVCFG3
// USERID = No Setting
 
// DEVCFG2
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (20x Multiplier)
#pragma config FPLLODIV = DIV_4         // System PLL Output Clock Divider (PLL Divide by 4)
 
// DEVCFG1
#pragma config FNOSC = FRCPLL           // Oscillator Selection Bits (Fast RC Osc with PLL)
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
#pragma config POSCMOD = OFF            // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = ON            // CLKO Output Signal Active on the OSCO Pin (Enabled)
#pragma config FPBDIV = DIV_1           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/1)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))
 
// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)
 
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
 
#include <xc.h>
 
void initADC(void);
int ReadADC(int ch);
 
main()
{
    initADC();              // Initialize ADC module
     
    int x,y;
     
    while(1)
    {
        x = ReadADC(0);     // Set x equal to channel 0 value
        if(x>521)           // When joystick is pushed one way
        {                   // (could be horizontal or vertical direction)
 
        }
        else if(x<501)      // Joystick pushed the other way
        {
 
        }
        else                // Joystick is at rest or being pushed in
        {                   // perpendicular direction only
 
        }
         
         
        y = ReadADC(1);     // Set y equal to channel 1 value
         
        if(y>521)           // When joystick is pushed one way
        {                   // (could be horizontal or vertical direction)
                            
        }
        else if(y<501)      // Joystick pushed the other way
        {
             
        }
        else                // Joystick is at rest or being pushed in
        {                   // perpendicular direction only
             
        }
    }
}
 
void initADC(void)
{
    AD1PCFGbits.PCFG0 = 0;          // Analog input in Analog mode
    AD1PCFGbits.PCFG1 = 0;
    TRISBbits.TRISB0 = 1;           // Pin set as input
    TRISBbits.TRISB1 = 1;
     
    AD1CHSbits.CH0NA = 0;           // Channel 0 negative input is VR-
    AD1CHSbits.CH0SA = 0;           // Channel 0 positive input is AN0
     
    AD1CON1bits.FORM = 0;           // Integer 16-bit output
     
    AD1CON1bits.SSRC = 0b111;       // Internal counter ends sampling and starts conversion
     
    AD1CSSL = 0;                    // No scanning required
     
    AD1CON2bits.VCFG = 0;           // Internal voltage references
     
    AD1CON2bits.CSCNA = 0;          // Do not scan inputs
     
    AD1CON2bits.BUFM = 0;           // Buffer configured as one 16-word buffer
     
    AD1CON2bits.ALTS = 0;           // Always use MUX A input multiplexer settings
     
    AD1CON3bits.ADRC = 0;           // Clock derived from PBclock
    AD1CON3bits.ADCS = 0b00111111;  // TAD = 2*TPB
     
    AD1CON3bits.SAMC = 0b11111;     // 31 TAD auto-sample time
     
    AD1CON1bits.ON = 1;             // A/D converter module is operating
}
 
int ReadADC(int ch)
{
    AD1CHSbits.CH0SA = ch;          // Select input channel
    AD1CON1bits.SAMP = 1;           // Start sampling
    while(!AD1CON1bits.DONE);       // Wait for conversion to complete
    return ADC1BUF0;                // Read conversion result
}