
#include "../../../Synth_system/Common.h"

#define VIDEO_DMA_ADDR (XPAR_AXI_VDMA_0_BASEADDR)
#define VIDEO_FRAME_BUFFERS_ADDR (0x10000000)
#define VIDEO_FRAME_BUFFER_ADDR(fb) (VIDEO_FRAME_BUFFERS_ADDR+0x00200000*(fb))

#define VDMA_MM2S_CTRL_OFF 0x00
#define VDMA_MM2S_CTRL_REG Reg32(VIDEO_DMA_ADDR+VDMA_MM2S_CTRL_OFF)
typedef struct
{
    union
    {
        u32 DWord;
        struct
        {
            u8 Run:1;
            u8 CircularPark:1;
            u8 Reset:1;
            u8 GenLockEn:1;
            u8 FrameCountEn:1;
            u8 RESERVED_1:2;
            u8 GenLockSrc:1;
            u8 ReadFbPtr:4;
            u8 FrameCountIrqEn:1;
            u8 DelayCountIrqEn:1;
            u8 ErrIrqEn:1;
            u8 RepeatEn:1;
            u8 IRQFrameCount;
            u8 IRQDelayCount;
        } Bitwise;
    } MM2S_Ctl;
} MM2S_Ctl;
#define VDMA_MM2S_CTRL_ST (*(MM2S_Ctl *)MEM32(VIDEO_DMA_ADDR+VDMA_MM2S_CTRL_OFF))


#define VDMA_MM2S_STATUS_OFF 0x04
#define VDMA_MM2S_STATUS_REG Reg32(VIDEO_DMA_ADDR+VDMA_MM2S_STATUS_OFF)
typedef struct
{
    union
    {
        u32 DWord;
        struct
        {
            u8 Halted:1;
            u8 RESERVED_1:3;
            u8 InternalErr:1;
            u8 SlaveErr:1;
            u8 DecodeErr:1;
            u8 StartOfFrameEarlyErr:1;
            u8 RESERVED_2:4;
            u8 FrameCountIrqEn:1;
            u8 DelayCountIrqEn:1;
            u8 ErrIrqEn:1;
            u8 RESERVED_3:1;
            u8 IRQFrameCount;
            u8 IRQDelayCount;
        } Bitwise;
    } MM2S_Status;
} MM2S_Status;
#define VDMA_MM2S_STATUS_ST (*(MM2S_Status *)MEM32(VIDEO_DMA_ADDR+VDMA_MM2S_STATUS_OFF))

#define VDMA_REG_IDX_OFF 0x14
#define VDMA_REG_IDX_REG Reg32(VIDEO_DMA_ADDR+VDMA_REG_IDX_OFF)
typedef struct
{
    union
    {
        u32 DWord;
        struct
        {
            u32 RegIdx:1;
            u32 RESERVED_1:31;
        } Bitwise;
    } MM2S_RegIdx;
} MM2S_RegIdx;
#define VDMA_REG_IDX_ST (*(MM2S_RegIdx *)MEM32(VIDEO_DMA_ADDR+VDMA_REG_IDX_OFF))

#define VDMA_PARK_PTR_OFF 0x28
#define VDMA_PARK_PTR_REG Reg32(VIDEO_DMA_ADDR+VDMA_PARK_PTR_OFF)
typedef struct
{
    union
    {
        u32 DWord;
        struct
        {
            u8 ReadFramePtrRef:5;
            u8 RESERVED_1:3;
            u8 WriteFramePtrRef:5;
            u8 RESERVED_2:3;
            u8 ReadFrameStore:5;
            u8 RESERVED_3:3;
            u8 WriteFrameStore:5;
            u8 RESERVED_4:3;
        } Bitwise;
    } ParkPtr;
} ParkPtr;
#define VDMA_PARK_PTR_ST (*(ParkPtr *)MEM32(VIDEO_DMA_ADDR+VDMA_PARK_PTR_OFF))

#define VDMA_VERSION_OFF 0x2C
#define VDMA_VERSION_REG Reg32(VIDEO_DMA_ADDR+VDMA_VERSION_OFF)
typedef struct
{
    union
    {
        u32 DWord;
        struct
        {
            u16 XilinxInternal;
            u16 Revision:4;
            u16 MinorVersion:8;
            u16 MajorVersion:4;
        } Bitwise;
    } VDMAVersion;
} VDMAVersion;
#define VDMA_VERSION_ST (*(VDMAVersion *)MEM32(VIDEO_DMA_ADDR+VDMA_VERSION_OFF))

#define VDMA_S2MM_CTRL_OFF 0x30
#define VDMA_S2MM_CTRL_REG Reg32(VIDEO_DMA_ADDR+VDMA_S2MM_CTRL_OFF)

#define VDMA_S2MM_STATUS_OFF 0x34
#define VDMA_S2MM_STATUS_REG Reg32(VIDEO_DMA_ADDR+VDMA_S2MM_STATUS_OFF)

#define VDMA_S2MM_ERR_INT_MASK_OFF 0x3C
#define VDMA_S2MM_ERR_INT_MASK_REG Reg32(VIDEO_DMA_ADDR+VDMA_S2MM_ERR_INT_MASK_OFF)

#define VDMA_S2MM_REG_IDX_OFF 0x44
#define VDMA_S2MM_REG_IDX_REG Reg32(VIDEO_DMA_ADDR+VDMA_S2MM_REG_IDX_OFF)

#define VDMA_MM2S_VSIZE_OFF 0x50
#define VDMA_MM2S_VSIZE_REG Reg32(VIDEO_DMA_ADDR+VDMA_MM2S_VSIZE_OFF)
typedef struct
{
    union
    {
        u32 DWord;
        struct
        {
            u16 Size:13;
            u16 RESERVED_1:3;
            u16 RESERVED_2;
        } Bitwise;
    } MM2S_VSize;
} MM2S_VSize;
#define VDMA_MM2S_VSIZE_ST (*(MM2S_VSize *)MEM32(VIDEO_DMA_ADDR+VDMA_MM2S_VSIZE_OFF))

#define VDMA_MM2S_HSIZE_OFF 0x54
#define VDMA_MM2S_HSIZE_REG Reg32(VIDEO_DMA_ADDR+VDMA_MM2S_HSIZE_OFF)
typedef struct
{
    union
    {
        u32 DWord;
        struct
        {
            u16 Size;
            u16 RESERVED_1;
        } Bitwise;
    } MM2S_HSize;
} MM2S_HSize;
#define VDMA_MM2S_HSIZE_ST (*(MM2S_HSize *)MEM32(VIDEO_DMA_ADDR+VDMA_MM2S_HSIZE_OFF))

#define VDMA_MM2S_FRAME_DELAY_STRIDE_OFF 0x58
#define VDMA_MM2S_FRAME_DELAY_STRIDE_REG Reg32(VIDEO_DMA_ADDR+VDMA_MM2S_FRAME_DELAY_STRIDE_OFF)
typedef struct
{
    union
    {
        u32 DWord;
        struct
        {
            u16 Stride;
            u8 RESERVED_1;
            u8 FrameDelay:5;
            u8 RESERVED_2:3;
        } Bitwise;
    } MM2S_DelayAndStride;
} MM2S_DelayAndStride;
#define VDMA_MM2S_FRAME_DELAY_STRIDE_ST (*(MM2S_DelayAndStride *)MEM32(VIDEO_DMA_ADDR+VDMA_MM2S_FRAME_DELAY_STRIDE_OFF))

#define VDMA_MM2S_START_ADDR_OFF(fb) (0x5C+(fb)*4)
#define VDMA_MM2S_START_ADDR_REG(fb) Reg32(VIDEO_DMA_ADDR+VDMA_MM2S_START_ADDR_OFF(fb))

#define VDMA_S2MM_VSIZE_OFF 0xA0
#define VDMA_S2MM_VSIZE_REG Reg32(VIDEO_DMA_ADDR+VDMA_S2MM_VSIZE_OFF)

#define VDMA_S2MM_HSIZE_OFF 0xA4
#define VDMA_S2MM_HSIZE_REG Reg32(VIDEO_DMA_ADDR+VDMA_S2MM_HSIZE_OFF)

#define VDMA_S2MM_FRAME_DELAY_STRIDE_OFF 0xA8
#define VDMA_S2MM_FRAME_DELAY_STRIDE_REG Reg32(VIDEO_DMA_ADDR+VDMA_S2MM_FRAME_DELAY_STRIDE_OFF)

#define VDMA_S2MM_START_ADDR_OFF(fb) (0xAC+((fb)-1)*4)
#define VDMA_S2MM_START_ADDR_REG(fb) Reg32(VIDEO_DMA_ADDR+VDMA_S2MM_START_ADDR_OFF(fb))

#define VDMA_ENABLE_VERITCAL_FLIP_OFF 0xEC
#define VDMA_ENABLE_VERITCAL_FLIP_REG Reg32(VIDEO_DMA_ADDR+VDMA_ENABLE_VERITCAL_FLIP_OFF)




#define VIDEO_CONTROLLER_ADDR (XPAR_APBSLAVE_BREAKOUT_2_BASEADDR)

#define VCTL_FRAME_PTR_OFF 0x00
#define VCTL_FRAME_PTR_REG Reg32(VIDEO_CONTROLLER_ADDR+VCTL_FRAME_PTR_OFF)

#define VCTL_SIGNALS_OFF 0x04
#define VCTL_SIGNALS_REG Reg32(VIDEO_CONTROLLER_ADDR+VCTL_SIGNALS_OFF)

#define VCTL_VDMA_STATUS_OFF 0x08
#define VCTL_VDMA_STATUS_REG Reg32(VIDEO_CONTROLLER_ADDR+VCTL_VDMA_STATUS_OFF)

#define VCTL_FIFO_LEVEL_OFF 0x0C
#define VCTL_FIFO_LEVEL_REG Reg32(VIDEO_CONTROLLER_ADDR+VCTL_FIFO_LEVEL_OFF)

#define VCTL_VDMA_FRAME_PTR_OFF 0x10
#define VCTL_VDMA_FRAME_PTR_REG Reg32(VIDEO_CONTROLLER_ADDR+VCTL_VDMA_FRAME_PTR_OFF)


int InitVideoDMA();





