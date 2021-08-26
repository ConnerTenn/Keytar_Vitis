
#include "USB_Controller.h"
#include "USB_Handlers.h"
#include "xusbps.h"
#include "xscugic.h"


XUsbPs USBdriver;
XUsbPs_DeviceConfig USBconfig;

u8 DMAmemory[1024] ALIGN32;

void InitUSB()
{
    PRINT("CPU1: Init USB\n");

    //== Initialize ==
    Usb_Config *config = XUsbPs_LookupConfig(XPAR_PS7_USB_0_DEVICE_ID);
    if (config == NULL) { PRINT(TERM_RED"CPU1: ERROR: Failed to find USB config\n"TERM_RESET); }

    int status;
    status = XUsbPs_CfgInitialize(&USBdriver, config, config->BaseAddress);
    if (XST_SUCCESS != status) { PRINT(TERM_RED"CPU1: ERROR: Failed to initialize USB driver\n"TERM_RESET); }


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
    if (XST_SUCCESS != status) { PRINT(TERM_RED"CPU1: ERROR: Failed to initialize USB driver\n"TERM_RESET); }


    //== Setup Handlers ==
    status = XUsbPs_EpSetHandler(&USBdriver, 0, XUSBPS_EP_DIRECTION_IN, USB_CtrlInHandler, &USBdriver);
    status = XUsbPs_EpSetHandler(&USBdriver, 0, XUSBPS_EP_DIRECTION_OUT, USB_CtrlOutHandler, &USBdriver);

    status = XUsbPs_EpSetIsoHandler(&USBdriver, 1, XUSBPS_EP_DIRECTION_IN, USB_SynthEventInISOHandler);
    status = XUsbPs_EpSetIsoHandler(&USBdriver, 1, XUSBPS_EP_DIRECTION_OUT, USB_SynthEventOutISOHandler);

    //== Setup Interrupts ==

    //== Start ==
    XUsbPs_Start(&USBdriver);
}

