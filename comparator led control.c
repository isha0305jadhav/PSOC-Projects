#include "project.h"
int main(void)
{
    CyGlobalIntEnable;
    Comp_1_Start();
    for(;;)
    {
        if(Comp_1_GetCompare() == 1)
        {
            LED_Write(1);   /* Turn LED ON */
        }
        else
        {
            LED_Write(0);   /* Turn LED OFF */
        }
    }
}
