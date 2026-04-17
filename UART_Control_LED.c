/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

#define LED_ON  1u
#define LED_OFF 0u

uint8 mode = 0u;   /* 0 = OFF, 1 = ON, 2 = BLINK */

void print_menu(void)
{
    UART_1_UartPutString("\r\n=== UART COMMAND MENU ===\r\n");
    UART_1_UartPutString("1 -> LED ON\r\n");
    UART_1_UartPutString("2 -> LED OFF\r\n");
    UART_1_UartPutString("3 -> LED BLINK\r\n");
    UART_1_UartPutString("m -> Show menu\r\n");
    UART_1_UartPutString("=========================\r\n");
}

int main(void)
{
    uint8 ch;

    CyGlobalIntEnable;

    UART_1_Start();

    LED_1_Write(LED_OFF);

    UART_1_UartPutString("UART Command Menu Started\r\n");
    print_menu();

    for(;;)
    {
        ch = UART_1_UartGetChar();

        if(ch != 0u)
        {
            UART_1_UartPutString("Received: ");
            UART_1_UartPutChar(ch);
            UART_1_UartPutString("\r\n");

            if(ch == '1')
            {
                mode = 1u;
                LED_1_Write(LED_ON);
                UART_1_UartPutString("LED ON\r\n");
            }
            else if(ch == '2')
            {
                mode = 0u;
                LED_1_Write(LED_OFF);
                UART_1_UartPutString("LED OFF\r\n");
            }
            else if(ch == '3')
            {
                mode = 2u;
                UART_1_UartPutString("LED BLINK MODE\r\n");
            }
            else if(ch == 'm' || ch == 'M')
            {
                print_menu();
            }
            else
            {
                UART_1_UartPutString("Invalid command\r\n");
            }
        }

        if(mode == 2u)
        {
            LED_1_Write(LED_ON);
            CyDelay(300);
            LED_1_Write(LED_OFF);
            CyDelay(300);
        }
    }
}
/* [] END OF FILE */
