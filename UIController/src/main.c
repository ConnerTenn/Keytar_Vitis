
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

#include "Sil9022.h"
#include "VideoDMA.h"


#include "lvgl/lvgl.h"



int Init()
{
    //Disable cache on OCM
    /** @todo Change to Macros. xil_mmu.h*/
    Xil_SetTlbAttributes(SHARED_ADDR,0x14de2); //S=b1 TEX=b100 AP=b11, Domain=b1111, C=b0, B=b0

    InitVideoDMA();
    
    Sil9022Init();

    return XST_SUCCESS;
}

u8 ActiveFB = 1;
void FlipBuffers()
{
    Xil_DCacheFlushRange(VIDEO_FRAME_BUFFER_ADDR(ActiveFB), 1080*1920*2);
    VDMA_PARK_PTR_ST.ParkPtr.Bitwise.ReadFramePtrRef = ActiveFB;
    ActiveFB = 1-ActiveFB;
}

void Draw()
{
    static u32 counter = 0;

    for (u32 y = 0, off = 0; y < 1080; y++)
    {
        for (u32 x = 0; x < 1920; x++)
        {
            u16 red = (0xFF*(y-counter)/1080);
            u16 green = (x-counter);
            u16 blue = 0xFF*(x+y-counter)/1080;
            *MEM16(VIDEO_FRAME_BUFFER_ADDR(ActiveFB)+off) = ((red&0x1F)<<11) | ((green&0x3F)<<5) | (blue&0x1F); off += 2;
        }
    }
    FlipBuffers();

    // PRINT("CPU1: VDMA Status 0x%08X    Video Status 0x%08X    Video Signals 0x%01X    FIFO Level %d\n", VDMA_MM2S_STATUS_REG, VCTL_VDMA_STATUS_REG, VCTL_SIGNALS_REG, VCTL_FIFO_LEVEL_REG);
    // PRINT("CPU1: Set Frame Ptr %d\n", VCTL_FRAME_PTR_REG);
    // PRINT("CPU1: VDMA Frame Ptr %d\n", VCTL_VDMA_FRAME_PTR_REG);

    counter+=5;
}

int main()
{
    PRINT("CPU1: Start!\n");

    if (Init() != XST_SUCCESS)
    {
        PRINT("CPU1: Init Failed\n");
        return XST_FAILURE;
    }

    PRINT("CPU1: Initialized!\n");
    // usleep(500*1000); //500ms


    PRINT("CPU1: Begin mainloop\n");
    // uint32_t count = 0;
    while (1)
    {
        // PRINT("CPU1: %lu\n", count++);

        Draw();


    }

    return 0;
}


