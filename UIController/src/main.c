
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


#include "../../Synth_system/Common.h"

#include "xil_mmu.h"
#include "sleep.h"

#include "Video/Sil9022.h"
#include "Video/VideoDMA.h"



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

    
    InitVideoDMA();
    
    Sil9022Init();


    usleep(500*1000); //500ms
    

    uint32_t count = 0;
    while (1)
    {
        VCTL_FRAME_PTR_REG = count % 2;
        PRINT("CPU1: %lu\n", count++);
        
        PRINT("CPU1: VDMA Status 0x%08X\n", VDMA_MM2S_STATUS_REG);
        PRINT("CPU1: Video Status 0x%08X\n", VCTL_VDMA_STATUS_REG);
        PRINT("CPU1: Video Signals 0x%01X\n", VCTL_SIGNALS_REG);
        PRINT("CPU1: FIFO Level %d\n", VCTL_FIFO_LEVEL_REG);
        PRINT("CPU1: VDMA Frame Ptr %d\n", VCTL_VDMA_FRAME_PTR_REG);

        usleep(2000*1000); //2000ms

    }

    return 0;
}


