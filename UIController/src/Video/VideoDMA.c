

#include "VideoDMA.h"


int InitVideoDMA()
{
    PRINT("CPU1: Init VideoDMA\n");

    VDMA_MM2S_CTRL_ST = (MM2S_Ctl){.MM2S_Ctl={.Bitwise={
            .IRQDelayCount = 0,
            .IRQFrameCount = 0,
            .RepeatEn = 0,
            .ErrIrqEn = 0,
            .DelayCountIrqEn = 0,
            .FrameCountIrqEn = 0,
            .ReadFbPtr = 0,
            .GenLockSrc = 0, //External GenLock
            .FrameCountEn = 0,
            .GenLockEn = 0,
            .Reset = 0,
            .CircularPark = 0, //Park Mode Enabled
            .Run = 0
        }}};


    return XST_SUCCESS;
}

