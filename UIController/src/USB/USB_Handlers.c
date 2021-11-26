
#include "USB_Handlers.h"

#include "xusbps.h"



void USB_CtrlRxHandler(void *callbackRef, u8 endpointNum, u8 eventType, void *data)
{
    PRINT("CPU1: USB Ctrl RX Handler\n");
    XUsbPs *usbDriver = (XUsbPs *)callbackRef;
    int status;

    switch (eventType)
    {
    //== Setup Packets ==
    case XUSBPS_EP_EVENT_SETUP_DATA_RECEIVED:
        {
            XUsbPs_SetupData setupData;
            status = XUsbPs_EpGetSetupData(usbDriver, endpointNum, &setupData);
            if (status == XST_SUCCESS)
            {
                //Handle the setup packet
                XUsbPs_Ch9HandleSetupPacket(usbDriver, &setupData);
            }
            break;
        }

    //== RX Packets ==
    case XUSBPS_EP_EVENT_DATA_RX:
        {
            u8 *buffer;
            u32 bufferLen;
            u32 handle;
            status = XUsbPs_EpBufferReceive(usbDriver, endpointNum, &buffer, &bufferLen, &handle);
            if (status == XST_SUCCESS)
            {
                XUsbPs_EpBufferRelease(handle);
            }
            break;
        }

    //== Unhandled Events ==
    default:
        break;
    }
}

void USB_CtrlTxHandler(void *callbackRef, u8 endpointNum, u8 eventType, void *data)
{
    PRINT("CPU1: USB Ctrl TX Handler\n");
    XUsbPs *usbDriver = (XUsbPs *)callbackRef;
    int status;

    switch (eventType)
    {
    //== TX Packets ==
    case XUSBPS_EP_EVENT_DATA_TX:
        {
            u8 *buffer;
            u32 bufferLen;
            // status = XUsbPs_EpBufferSend(usbDriver, endpointNum, &buffer, &bufferLen);
            break;
        }

    //== Unhandled Events ==
    default:
        break;
    }
}


u8 RecvBuffer[1024];
void USB_SynthEventIsoRxHandler(void *callbackRef, u32 requestedBytes, u32 bytesTXed)
{
    PRINT("CPU1: USB ISO RX Handler\n");
    XUsbPs *usbDriver = (XUsbPs *)callbackRef;



    // XUsbPs_EpDataBufferReceive(usbDriver, 1, RecvBuffer, size);
}

void USB_SynthEventIsoTxHandler(void *callbackRef, u32 requestedBytes, u32 bytesTXed)
{
    PRINT("CPU1: USB ISO TX Handler\n");
    XUsbPs *usbDriver = (XUsbPs *)callbackRef;

    u8 buffer[] = "USB test\n";
    u32 bufferLen = sizeof(buffer);
    u32 handle;
    XUsbPs_EpBufferSend(usbDriver, 1, (const u8 *)buffer, bufferLen);
}



