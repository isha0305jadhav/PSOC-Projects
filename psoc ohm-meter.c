PSoC 4200M UART Command Control LED Project  

Project Summary: To design a simple embedded project on the PSoC 4200M where an LED is controlled through UART commands sent from a serial terminal. The project demonstrates UART communication, digital output control, and basic firmware logic using PSoC Creator. 

Procedure:  

1. Open PSoC Creator and create a new project for the PSoC 4200M device or CY8CKIT-043 board.  

2. In the TopDesign schematic, add a UART component and one Digital Output Pin component for the LED.  

3. Configure the UART with a standard baud rate such as 9600 bps, 8 data bits, no parity, and 1 stop bit.  

4. Assign the UART TX and RX pins in the Design Wide Resources window according to the kit connection.  

5. Assign the LED pin to a suitable GPIO connected to the on-board LED or an external LED pin if used. 

 6. Generate the application and write firmware to continuously check received UART data. 

7. Define simple commands such as '1' to turn the LED ON and '0' to turn the LED OFF.  

8. Build the project and program the PSoC 4200M board using the connected programmer/debugger. 

 9. Open a serial terminal on the computer, select the correct COM port, and match the baud rate settings.  

10. Send UART commands from the terminal and verify that the LED turns ON or OFF based on the received command.  

Code: PSOC-Projects/UART_Control_LED.c at main · isha0305jadhav/PSOC-Projects 

Video Output: https://photos.app.goo.gl/UqUaY14BgT3T6aZi9 

 

 

 

 

PSoC 4200M Comparator LED Control  

Project Summary: To build a simple PSoC 4200M project in which the on-board LED turns ON when the comparator input sees 3.3V and turns OFF when the input is at 0V. This project demonstrates comparator usage, GPIO output control, simple jumper-wire testing, and basic firmware integration in PSoC Creator 

Procedure: 

1. Open PSoC Creator and create a new project for the CY8CKIT-043 / PSoC 4200M device.  

2. In TopDesign, place one Comparator component and one Digital Output Pin component for the LED.  

3. Configure the Comparator so that the positive input comes from an external pin, for example P2[0].  

4. Configure the negative input of the Comparator to use the internal reference or threshold setting selected in the component configuration. 

 5. Configure the LED pin as a digital output and connect it to the board LED pin or the GPIO you selected for the LED. 

 6. In the Pins assignment window, map the comparator input pin to P2[0] and the LED pin to the desired LED GPIO.  

7. Generate the application so PSoC Creator creates the required APIs for the Comparator and LED pin. 

 8. Use a jumper wire to connect P2[0] to the board 3.3V supply for a HIGH comparator input test. 

 9. For the LOW comparator input test, move the same jumper wire from 3.3V to GND and apply it to P2[0].  

10. Add firmware that continuously reads the comparator output and writes the result to the LED. 

11. Build the project and program the board.  

12. Verify operation: when P2[0] is tied to 3.3V, the comparator output should go HIGH and the LED should turn ON; when P2[0] is tied to GND, the LED should turn OFF 

Code:PSOC-Projects/comparator led control.c at main · isha0305jadhav/PSOC-Projects 

Video: I will provide a link in a while, My GND and 3.3V pin on board having dry solder. 

Project Title: PSoC Auto Ranging Ohm Meter 

 

Project Summary: To design and implement an auto-ranging Ohm Meter using the PSoC 4 platform. The system measures unknown resistance by injecting a known current using the IDAC module and measuring the resulting voltage drop using a 12-bit ADC. The resistance is calculated using Ohm’s Law and displayed on a 16x2 LCD. The project demonstrates analog interfacing, ADC usage, IDAC configuration, and embedded firmware design. 

Objective 

    To measure unknown resistance using embedded hardware  

    To implement auto-ranging using programmable current source (IDAC)  

    To interface ADC and LCD with PSoC  

    To apply Ohm’s Law in embedded systems  

    To understand analog + digital integration in PSoC  

Hardware Components 

    PSoC 4 Prototyping Kit  

    16x2 LCD Display  

    Breadboard  

    Jumper wires  

 Working Principle: The project is based on Ohm’s Law: 

                                          I=V/R  

    IDAC injects a known current (µA) into the unknown resistor  

    A voltage drop appears across the resistor  

    ADC measures this voltage  

    PSoC calculates resistance using:  

    Voltage (from ADC)  

    Current (from IDAC setting)  

 Auto-Ranging Concept 

    IDAC can generate current from 1.2 µA to 306 µA  

    Start with maximum current  

    If voltage exceeds ADC range:  

    Reduce current step-by-step  

    Continue until voltage is within measurable range (0–2V)  

    Then calculate resistance  

 

Procedure 

    Open PSoC Creator and create a new project for PSoC 4 device  

    Add following components in TopDesign:  

    ADC (12-bit)  

    IDAC  

    LCD (16x2)  

    Timer (optional for reboot/debug)  

    Configure ADC:  

    12-bit resolution  

    Internal reference ~1.024V  

    Range: 0–2V  

    Configure IDAC:  

    Set current range (1.2 µA steps)  

    Connect unknown resistor between IDAC output and ground  

    Initialize LCD, ADC, and IDAC in firmware  

    Implement loop:  

    Set IDAC current  

    Measure voltage using ADC  

    Adjust current (auto-ranging)  

    Calculate resistance using formula  

    Display resistance on LCD  

    Build and program the board  

    Verify output with different resistors 

 

Output: #include <project.h> 
 
int current =0; 
int voltage =0; 
int resistance=0; 
char str_resistance[5]; 
unsigned int IDAC_Val=0xff; 
//Prototype the ISR Handler 
 
CY_ISR_PROTO(RebootISR_Handler); 
 
// Implement ISR 
CY_ISR(RebootISR_Handler) 
{ 
   // Enters Bootloader here and shows message 
 LCD_Char_ClearDisplay(); 
   CyGlobalIntDisable; 
   LCD_Char_PrintString(" Restarting... "); 
   CyDelay(500); 
   LCD_Char_ClearDisplay(); 
   LCD_Char_PrintString("READY to PROGRAM"); 
   LCD_Char_Position (1,0); 
   LCD_Char_PrintString("< Upload Code > "); 
    
   // Restart and enter bootloader  
   Bootloadable_Load(); 
 
    
} 
 
 
 
int main() 
{   int c=4095; 
   LCD_Char_Start(); 
 // LCD_Char_LoadCustomFonts(); 
   
   Reboot_Timer_Start(); 
   ADC_Start(); 
   IDAC_Inject_Start(); 
    
 
    
   // Enable ISR and clear pending, if any ! 
   RebootISR_ClearPending(); 
   RebootISR_StartEx( RebootISR_Handler ); 
   CyGlobalIntEnable; 
 
  
   IDAC_Val=0xff; 
    IDAC_Inject_SetValue(IDAC_Val); 
   ADC_StartConvert(); 
    
   LCD_Char_PrintString("PSoC Auto Range"); 
   LCD_Char_Position(1,0); 
   LCD_Char_PrintString("  Ohms Meter  "); 
   CyDelay(2000); 
   LCD_Char_ClearDisplay(); 
 
 for(;;) 
 { 
   IDAC_Val=0xff; 
   c=4095; 
   
   
   // the following while loop does the AUTO RANGING 
while((IDAC_Val>0)&&(c>=4000)) 
{ 
    
   IDAC_Val=IDAC_Val-0x01; 
   IDAC_Inject_SetValue(IDAC_Val); 
   CyDelay(3); 
   while( ADC_IsEndConversion(ADC_RETURN_STATUS)){} 
   c=ADC_GetResult16(0); 
  // LCD_Char_ClearDisplay(); 
   CyDelay(2); 
     
   
} 
   
 
if (c<4000) 
{ 
   IDAC_Inject_SetValue(IDAC_Val); 
   CyDelay(1); 
   // while( ADC_IsEndConversion(ADC_RETURN_STATUS)){} 
   //  c=ADC_GetResult16(0); 
   current= IDAC_Val*1.2;    // in uAmp 
   voltage=c*1000/2;  // in uVolt 
 
    resistance= voltage/current; 
    
 //  sprintf(str_resistance,"%f",resistance); 
   LCD_Char_ClearDisplay(); 
   LCD_Char_PrintString("   Resistance"); 
   LCD_Char_Position(1,3); 
 //  LCD_Char_PrintString("in Ohms= "); 
   if (resistance<950000) 
   {LCD_Char_PrintU32Number(resistance); 
    
    LCD_Char_PrintString(" "); 
    
    LCD_Char_PutChar(LCD_Char_CUSTOM_0); 
   } 
   else  
   { 
       LCD_Char_ClearDisplay(); 
       LCD_Char_PrintString("Connect Resistor"); 
      
   } 
     
   CyDelay(300); 
    
  
    
 
 } 
 
 
} 
 
 
// Num to String 
} 
 

 
