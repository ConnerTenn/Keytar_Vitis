
#include "VideoController.h"

#include "xil_mmu.h"
#include "xil_cache.h"

#define BLOCK_SIZE_1MB 0x100000U
#define BLOCK_SIZE_2MB 0x200000U

int InitVideoController()
{
    PRINT("CPU1: Initializing Video Controller\n");
    VIDEO_CTRL_ACTIVATE_REG = 0;

    VIDEO_CTRL_FB1ADDR_REG = VIDEO_FRAME_BUFFER_ADDR(0);
    VIDEO_CTRL_FB2ADDR_REG = VIDEO_FRAME_BUFFER_ADDR(1);

    if (VIDEO_CTRL_FB1ADDR_REG != VIDEO_FRAME_BUFFER_ADDR(0) ||
        VIDEO_CTRL_FB2ADDR_REG != VIDEO_FRAME_BUFFER_ADDR(1))
    {
        PRINT("CPU1: " TERM_RED "ERROR: Video Controller Not Responding\n" TERM_RESET);
        return XST_FAILURE;
    }

    for (u8 fb=0; fb<=1; fb++)
    {
        for (u32 off=0; off<VIDEO_FRAME_BUFFER_SIZE; off+=BLOCK_SIZE_1MB)
        {
            Xil_SetTlbAttributes(VIDEO_FRAME_BUFFER_ADDR(fb)+off, NORM_NONCACHE);
        }
    }

    VIDEO_CTRL_FBSIZE_REG = VIDEO_FRAME_BUFFER_SIZE;
    if (VIDEO_CTRL_FBSIZE_REG != VIDEO_FRAME_BUFFER_SIZE)
    {
        PRINT("CPU1: " TERM_RED "ERROR: Video Controller Not Responding\n" TERM_RESET);
        return XST_FAILURE;
    }

    VIDEO_CTRL_FBSELECT_REG = 1;
    while (VIDEO_CTRL_FBSELECT_REG != 1) {}


    VIDEO_CTRL_ACTIVATE_REG = 1;


    PRINT("CPU1: Video Controller Initialized\n");
    return XST_SUCCESS;
}

