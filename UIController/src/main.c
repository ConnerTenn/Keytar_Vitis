
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

    lv_init();

    return XST_SUCCESS;
}

// u8 ActiveFB = 1;
// void FlipBuffers()
// {
//     Xil_DCacheFlushRange(VIDEO_FRAME_BUFFER_ADDR(ActiveFB), 1080*1920*2);
//     VDMA_PARK_PTR_ST.ParkPtr.Bitwise.ReadFramePtrRef = ActiveFB;
//     ActiveFB = 1-ActiveFB;
// }

// void Draw()
// {
//     static u32 counter = 0;

//     for (u32 y = 0, off = 0; y < 1080; y++)
//     {
//         for (u32 x = 0; x < 1920; x++)
//         {
//             u16 red = (0xFF*(y-counter)/1080);
//             u16 green = (x-counter);
//             u16 blue = 0xFF*(x+y-counter)/1080;
//             *MEM16(VIDEO_FRAME_BUFFER_ADDR(ActiveFB)+off) = ((red&0x1F)<<11) | ((green&0x3F)<<5) | (blue&0x1F); off += 2;
//         }
//     }
//     FlipBuffers();

//     // PRINT("CPU1: VDMA Status 0x%08X    Video Status 0x%08X    Video Signals 0x%01X    FIFO Level %d\n", VDMA_MM2S_STATUS_REG, VCTL_VDMA_STATUS_REG, VCTL_SIGNALS_REG, VCTL_FIFO_LEVEL_REG);
//     // PRINT("CPU1: Set Frame Ptr %d\n", VCTL_FRAME_PTR_REG);
//     // PRINT("CPU1: VDMA Frame Ptr %d\n", VCTL_VDMA_FRAME_PTR_REG);

//     counter+=5;
// }

void FlushCallback(struct _disp_drv_t *dispDrv, const lv_area_t *area, lv_color_t *color_p)
{
    u8 fb = -1;
    if ((u32)color_p == VIDEO_FRAME_BUFFER_ADDR(0)) { fb = 0; }
    else if ((u32)color_p == VIDEO_FRAME_BUFFER_ADDR(1)) { fb = 1; }

    if (fb <= 1)
    {
        Xil_DCacheFlushRange(VIDEO_FRAME_BUFFER_ADDR(fb), 1080*1920*2);
        VDMA_PARK_PTR_ST.ParkPtr.Bitwise.ReadFramePtrRef = fb;
    }
    else
    {
        PRINT("CPU1:" TERM_RED "ERROR: Flush called for invalid address\n" TERM_RESET);
    }

    lv_disp_flush_ready(dispDrv);
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


    PRINT("CPU1: Setting up display!\n");
    lv_disp_buf_t dispBuf; //Display Buffer descriptor
    lv_disp_buf_init(&dispBuf, (void *)VIDEO_FRAME_BUFFER_ADDR(0), (void *)VIDEO_FRAME_BUFFER_ADDR(1), 1080*1920*2);

    lv_disp_drv_t dispDrv; //Display Driver descriptor
    lv_disp_drv_init(&dispDrv);
    dispDrv.buffer = &dispBuf;
    dispDrv.flush_cb = FlushCallback; //Attach Flush Callback

    //Register the driver and save pointer to the created display
    lv_disp_t *display = lv_disp_drv_register(&dispDrv);
    (void *)display; //Disable unused variable warning

    lv_obj_t *screen = lv_scr_act();

    lv_obj_t *rect = lv_obj_create(screen, NULL);
    lv_obj_set_style_local_bg_color(rect, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x00FFFF));
    lv_obj_set_size(rect, 100, 50);



    PRINT("CPU1: Begin mainloop\n");
    // uint32_t count = 0;
    while (1)
    {
        // PRINT("CPU1: %lu\n", count++);
        // Draw();


        lv_tick_inc(1); //Increment 1 ms

        lv_task_handler();

        usleep(1*1000); //1ms
    }

    return 0;
}


