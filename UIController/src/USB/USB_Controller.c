
#include "USB_Controller.h"
#include "USB_Handlers.h"
#include "../Interrupts.h"

#include "xusbps.h"


XUsbPs USBdriver;
XUsbPs_DeviceConfig USBconfig;

u8 DMAmemory[1024] ALIGN32;

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

