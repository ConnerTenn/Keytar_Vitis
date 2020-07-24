

#include "VideoDMA.h"


int InitVideoDMA()
{
    PRINT("CPU1: Init VideoDMA\n");

    // u32 rawversion = VDMA_VERSION_REG;
    PRINT("CPU1: Read VideoDMA Version:");
    VDMAVersion version = VDMA_VERSION_ST;//*(VDMAVersion *)(&rawversion);
    PRINT("0x%08X\n    Major: 0x%01X\n    Minor: 0x%02X\n    Revision: 0x%01X\n    Internal: 0x%04X\n", 
        version.VDMAVersion.DWord,
        version.VDMAVersion.Bitwise.MajorVersion,
        version.VDMAVersion.Bitwise.MinorVersion,
        version.VDMAVersion.Bitwise.Revision,
        version.VDMAVersion.Bitwise.XilinxInternal);


    VDMA_MM2S_CTRL_ST = (MM2S_Ctl){.MM2S_Ctl={.Bitwise={
            .Run = 0,
            .CircularPark = 0, //Park Mode Enabled
            .Reset = 0,
            .GenLockEn = 0,
            .FrameCountEn = 0,
            .GenLockSrc = 0, //External GenLock
            .ReadFbPtr = 0,
            .FrameCountIrqEn = 0,
            .DelayCountIrqEn = 0,
            .ErrIrqEn = 0,
            .RepeatEn = 0,
            .IRQFrameCount = 0,
            .IRQDelayCount = 0,
        }}};

    PRINT("CPU1: Set Frame PTR\n");
    V_FRAME_PTR_REG = 2;
    PRINT("CPU1: Frame PTR set to: %d\n", V_FRAME_PTR_REG);




    return XST_SUCCESS;
}

