
#include "Interrupts.h"

XScuGic GICdriver;

void InitializeInterrupt()
{
    PRINT("CPU1: Initialize Interrupts\n");

    s32 status;

    /*== Initalize ==*/
    XScuGic_Config *config = XScuGic_LookupConfig(XPAR_SCUGIC_SINGLE_DEVICE_ID);
    if (config == NULL) { PRINT(TERM_RED"CPU1: ERROR: Failed to find GIC config\n"TERM_RESET); }

    status = XScuGic_CfgInitialize(&GICdriver, config, config->CpuBaseAddress);
    if (status != XST_SUCCESS) { PRINT(TERM_RED"CPU1: ERROR: Failed to initialize the GIC\n"TERM_RESET); }
    Xil_ExceptionInit();

    // Connect the interrupt controller interrupt handler to the hardware interrupt handling logic in the processor.
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, &GICdriver);

    //Enable interrupts in the Processor
    Xil_ExceptionEnableMask(XIL_EXCEPTION_IRQ);

    PRINT("CPU1: Interrupts Initialized\n");
}

void InterruptAttach(u32 interruptID, Xil_InterruptHandler handler, void *callbackRef)
{
    int status = XScuGic_Connect(&GICdriver, interruptID, handler, callbackRef);
    if (status != XST_SUCCESS) { PRINT(TERM_RED"CPU1: ERROR: Failed to attach GIC handler\n"TERM_RESET); }

    XScuGic_Enable(&GICdriver, interruptID);
}

