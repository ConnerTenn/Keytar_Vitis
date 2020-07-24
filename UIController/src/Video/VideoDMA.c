

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
            .Run = 1,
            .CircularPark = 1,
            .Reset = 0,
            .GenLockEn = 1,
            .FrameCountEn = 0,
            .GenLockSrc = 0, //0:External GenLock  1:Internal GenLock
            .ReadFbPtr = 0,
            .FrameCountIrqEn = 0,
            .DelayCountIrqEn = 0,
            .ErrIrqEn = 0,
            .RepeatEn = 0,
            .IRQFrameCount = 1,
            .IRQDelayCount = 0,
        }}};

    VDMA_MM2S_FRAME_DELAY_STRIDE_ST = (MM2S_DelayAndStride){.MM2S_DelayAndStride={.Bitwise={
            .FrameDelay = 1,
            .Stride = 1920*3
        }}};

    PRINT("CPU1: Set Frame Buffer Addresses\n");

    VDMA_MM2S_START_ADDR_REG(0) = VIDEO_FRAME_BUFFER_ADDR(0);
    VDMA_MM2S_START_ADDR_REG(1) = VIDEO_FRAME_BUFFER_ADDR(1);
    VDMA_MM2S_START_ADDR_REG(2) = VIDEO_FRAME_BUFFER_ADDR(2);

    PRINT("CPU1: Set Frame Size, which starts video\n");
    VDMA_MM2S_HSIZE_REG = 1920*3;
    VDMA_MM2S_VSIZE_REG = 1080;

    PRINT("CPU1: Set Frame PTR\n");
    VCTL_FRAME_PTR_REG = 1;
    PRINT("CPU1: Frame PTR set to: %d\n", VCTL_FRAME_PTR_REG);

    PRINT("CPU1: VDMA Status 0x%08X\n", VDMA_MM2S_STATUS_REG);
    PRINT("CPU1: Video Status 0x%08X\n", VCTL_VDMA_STATUS_REG);
    PRINT("CPU1: Video Signals 0x%01X\n", VCTL_SIGNALS_REG);
    PRINT("CPU1: FIFO Level %d\n", VCTL_FIFO_LEVEL_REG);
    PRINT("CPU1: VDMA Frame Ptr %d\n", VCTL_VDMA_FRAME_PTR_REG);


    u32 off;
    off = 0;
    for (u32 y = 0; y < 1080; y++)
    {
        for (u32 x = 0; x < 1920; x++)
        {
            *MEM8(VIDEO_FRAME_BUFFER_ADDR(0)+off) = 0x00; off++;
            *MEM8(VIDEO_FRAME_BUFFER_ADDR(0)+off) = 0xFF; off++;
            *MEM8(VIDEO_FRAME_BUFFER_ADDR(0)+off) = 0xFF; off++;
        }
    }
    off = 0;
    for (u32 y = 0; y < 1080; y++)
    {
        for (u32 x = 0; x < 1920; x++)
        {
            *MEM8(VIDEO_FRAME_BUFFER_ADDR(1)+off) = 0xFF; off++;
            *MEM8(VIDEO_FRAME_BUFFER_ADDR(1)+off) = 0xFF; off++;
            *MEM8(VIDEO_FRAME_BUFFER_ADDR(1)+off) = 0x00; off++;
        }
    }
    off = 0;
    for (u32 y = 0; y < 1080; y++)
    {
        for (u32 x = 0; x < 1920; x++)
        {
            *MEM8(VIDEO_FRAME_BUFFER_ADDR(2)+off) = 0xFF; off++;
            *MEM8(VIDEO_FRAME_BUFFER_ADDR(2)+off) = 0x00; off++;
            *MEM8(VIDEO_FRAME_BUFFER_ADDR(2)+off) = 0xFF; off++;
        }
    }


    return XST_SUCCESS;
}

