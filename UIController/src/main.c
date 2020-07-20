
/**
* Hello World program using XUartPs driver in polled mode
*
* The example uses the default setting in the XUartPs driver:
*	. baud rate 115200
*	. 8 bit data
*	. 1 stop bit
*	. no parity
*
* @note
* This example requires an external SchmartModule connected to the pins for
* the device to display the 'Hello World' message onto a hyper-terminal.
*
*/


#include "../../Synth_system/common.h"

#include "xil_mmu.h"

#include "sleep.h"



int Init()
{
    //Disable cache on OCM
    Xil_SetTlbAttributes(SHARED_ADDR,0x14de2); //S=b1 TEX=b100 AP=b11, Domain=b1111, C=b0, B=b0

    return XST_SUCCESS;
}

int main()
{
    if (Init() != XST_SUCCESS)
    {
        PRINT("CPU1: Init Failed\n");
        return XST_FAILURE;
    }
    PRINT("CPU1: Start!\n");
    usleep(250*1000); //250ms

    uint32_t count = 0;
    while (1)
    {
        xil_printf("CPU1: %lu\n", count++);
        usleep(500*1000); //500ms

    }

    return 0;
}


