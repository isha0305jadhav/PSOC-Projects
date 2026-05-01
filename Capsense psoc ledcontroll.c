#include "project.h"
#include <stdio.h>
char buffer[50];
int main(void)
{
CyGlobalIntEnable;
UART_Start();
CapSense_Start();
CapSense_InitializeAllBaselines();
for(;;)
{
CapSense_ScanAllWidgets();
while(CapSense_IsBusy());
CapSense_ProcessAllWidgets();
if(CapSense_IsWidgetActive(CapSense_BUTTON0_WDGT_ID))
{
sprintf(buffer, "Button Pressed\r\n");
}
else
{
sprintf(buffer, "Button Released\r\n");
}
UART_PutString(buffer);
CyDelay(200);
}
}
