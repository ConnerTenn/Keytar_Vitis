
#include "USB_Controller.h"
#include "USB_Handlers.h"
#include "../Interrupts.h"

#include "xusbps.h"


XUsbPs USBdriver;
XUsbPs_DeviceConfig USBconfig;

u8 DMAmemory[1024] ALIGN32;



/*
 * Device Descriptors
 */
USB_STD_DEV_DESC __attribute__ ((aligned(16))) USBDeviceDesc = {
    /*
     * USB 2.0
     */
    sizeof(USB_STD_DEV_DESC),  /* bLength */
    XUSBPS_TYPE_DEVICE_DESC,   /* bDescriptorType */
    0x0200,                    /* bcdUSB 2.0 */
    XUSBPS_CLASS_VENDOR,       /* bDeviceClass */
    0x10,                      /* bDeviceSubClass */
    0x01,                      /* bDeviceProtocol */
    0x40,                      /* bMaxPackedSize0 */
    0x03Fd,                    /* idVendor */
    0x0200,                    /* idProduct */
    0x0100,                    /* bcdDevice */
    0x01,                      /* iManufacturer */
    0x02,                      /* iProduct */
    0x03,                      /* iSerialNumber */
    0x01                       /* bNumConfigurations */
};

USB_CONFIG __attribute__ ((aligned(16))) USBConfig = {
    {/* Std Config*/
        sizeof(USB_STD_CFG_DESC),  /* bLength */
        XUSBPS_TYPE_CONFIG_DESC,   /* bDescriptorType */
        sizeof(USB_CONFIG),        /* wTotalLength */
        0x01,                      /* Num interfaces */
        0x01,                      /* Num configuration values */
        0x00,                      /* Configuration string */
        0xC0,                      /* bmAttribute */
        0x01                       /* bMaxPower */
    },
    {/* Interface Config */
        sizeof(USB_STD_IF_DESC),  /* Interface Descriptor size 9 bytes */
        XUSBPS_TYPE_IF_CFG_DESC,  /* This is an interface descriptor */
        0x00,                     /* Interface number 0 */
        0x00,                     /* Alternate set 0 */
        0x01,                     /* Number of end points */
        XUSBPS_CLASS_VENDOR,      /* Audio device */
        0xE6,                     /* Audio Control */
        0x21,                     /* Interface Protocol */
        0x00                      /* iInterface */
    },
};

char *StringList[] = {
    "UNUSED",
    "Xilinx",
    "Custom Synth Device",
    "E621E926",
    "Default Configuration",
    "Default Interface",
};



void InitUSB()
{
    PRINT("CPU1: Initialize USB\n");

    //== Initialize ==
    Usb_Config *config = XUsbPs_LookupConfig(XPAR_PS7_USB_0_DEVICE_ID);
    if (config == NULL) { PRINT(TERM_RED"CPU1: ERROR: Failed to find USB config\n"TERM_RESET); }

    int status;
    status = XUsbPs_CfgInitialize(&USBdriver, config, config->BaseAddress);
    if (status != XST_SUCCESS) { PRINT(TERM_RED"CPU1: ERROR: Failed to initialize USB driver\n"TERM_RESET); }


    //== Setup Endpoints ==
    //Control
    USBconfig.EpCfg[0] = (XUsbPs_EpConfig){
        .Out.Type = XUSBPS_EP_TYPE_CONTROL,
        .Out.NumBufs = 2,
        .Out.BufSize = 64,
        .Out.MaxPacketSize = 64,
        .In.Type = XUSBPS_EP_TYPE_CONTROL,
        .In.NumBufs = 2,
        .In.MaxPacketSize = 6,
    };

    //Synth Events
    USBconfig.EpCfg[1] = (XUsbPs_EpConfig){
        .Out.Type = XUSBPS_EP_TYPE_ISOCHRONOUS,
        .Out.NumBufs = 16,
        .Out.BufSize = 1024,
        .Out.MaxPacketSize = 64,
        .In.Type = XUSBPS_EP_TYPE_ISOCHRONOUS,
        .In.NumBufs = 16,
        .In.MaxPacketSize = 64,
    };

    USBconfig.NumEndpoints = 2;

    USBconfig.DMAMemPhys = (u32)DMAmemory;

    status = XUsbPs_ConfigureDevice(&USBdriver, &USBconfig);
    if (status != XST_SUCCESS) { PRINT(TERM_RED"CPU1: ERROR: Failed to initialize USB driver\n"TERM_RESET); }


    //== Setup Handlers ==
    status = XUsbPs_EpSetHandler(&USBdriver, 0, XUSBPS_EP_DIRECTION_OUT, USB_CtrlRxHandler, &USBdriver);
    status = XUsbPs_EpSetHandler(&USBdriver, 0, XUSBPS_EP_DIRECTION_IN, USB_CtrlTxHandler, &USBdriver);

    status = XUsbPs_EpSetIsoHandler(&USBdriver, 1, XUSBPS_EP_DIRECTION_OUT, USB_SynthEventIsoRxHandler);
    status = XUsbPs_EpSetIsoHandler(&USBdriver, 1, XUSBPS_EP_DIRECTION_IN, USB_SynthEventIsoTxHandler);

    //== Setup Interrupts ==
    //Connect the device driver interrupt handler
    InterruptAttach(XPAR_XUSBPS_0_INTR, XUsbPs_IntrHandler, &USBdriver);
    XUsbPs_IntrEnable(&USBdriver, XUSBPS_IXR_UR_MASK | XUSBPS_IXR_UI_MASK);

    //== Start ==
    XUsbPs_Start(&USBdriver);

    PRINT("CPU1: USB Initialized\n");
}



void XUsbPs_ClassReq(XUsbPs *InstancePtr, XUsbPs_SetupData *SetupData)
{
    // s32 Status;
    // u8 Error = 0;
    // u32 ReplyLen;
    // static u8 Reply[XUSBPS_REQ_REPLY_LEN] ALIGNMENT_CACHELINE;


    // switch (SetupData->bRequest) 
    // {
    //     default:
    // }
}


u32 XUsbPs_Ch9SetupDevDescReply(u8 *bufPtr, u32 bufLen)
{
    /* Check buffer pointer is there and buffer is big enough. */
    if (!bufPtr) { return 0; }
    if (bufLen < sizeof(USB_STD_DEV_DESC)) { return 0; }

    memcpy(bufPtr, &USBDeviceDesc, sizeof(USB_STD_DEV_DESC));

    return sizeof(USB_STD_DEV_DESC);
}

u32 XUsbPs_Ch9SetupCfgDescReply(u8 *bufPtr, u32 bufLen)
{
    /* Check buffer pointer is OK and buffer is big enough. */
    if (!bufPtr) { return 0; }
    if (bufLen < sizeof(USB_STD_CFG_DESC)) { return 0; }

    memcpy(bufPtr, (u8 *)&USBConfig, sizeof(USB_CONFIG));

    return sizeof(USB_CONFIG);
}

u32 XUsbPs_Ch9SetupStrDescReply(u8 *bufPtr, u32 bufLen, u8 index)
{
    u8 buffer[128];
    //Assign to buffer because of dynamic sized element
    USB_STD_STRING_DESC *stringDesc = (USB_STD_STRING_DESC *)buffer;

    if (!bufPtr) { return 0; }
    if (index >= sizeof(StringList) / sizeof(char *)) { return 0; }

    char *string = StringList[index];
    u32 stringLen = strlen(string);


    //index 0 is special as we can not represent the string required in
    //the table above. Therefore we handle index 0 as a special case.
    if (index==0)
    {
        stringDesc->bLength = 4;
        stringDesc->bDescriptorType = XUSBPS_TYPE_STRING_DESC;
        stringDesc->wLANGID[0] = 0x0409;
    }
    //All other strings can be pulled from the table above.
    else 
    {
        stringDesc->bLength = stringLen * 2 + 2;
        stringDesc->bDescriptorType = XUSBPS_TYPE_STRING_DESC;

        for (int i=0; i<stringLen; i++) 
        {
            stringDesc->wLANGID[i] = (u16)string[i];
        }
    }
    u32 descLen = stringDesc->bLength;


    //Check if the provided buffer is big enough to hold the descriptor.
    if (descLen > bufLen) { return 0; }

    memcpy(bufPtr, stringDesc, descLen);

    return descLen;
}

void XUsbPs_SetConfiguration(XUsbPs *InstancePtr, int ConfigIdx)
{
    u8 state = InstancePtr->AppData->State;
    XUsbPs_SetConfigDone(InstancePtr, 0U);

    switch (state) {
        case XUSBPS_STATE_DEFAULT:
            break;

        case XUSBPS_STATE_ADDRESS:
            InstancePtr->AppData->State = XUSBPS_STATE_CONFIGURED;
            break;

        case XUSBPS_STATE_CONFIGURED:
            break;

        default:
            break;
    }
}

void XUsbPs_SetConfigurationApp(XUsbPs *InstancePtr, XUsbPs_SetupData *SetupData)
{
}

void XUsbPs_SetInterfaceHandler(XUsbPs *InstancePtr, XUsbPs_SetupData *SetupData)
{
}

