

#include "xparameters.h"
#include "xil_types.h"
#include "xil_io.h"

#include "xuartps.h"
#include "xil_printf.h"


#define SHARED_ADDR (0xFFFF0000)

#define PRINT_MUTEX_OFF (0x0000)
#define PRINT_MUTEX_ADDR (SHARED_ADDR+PRINT_MUTEX_OFF)


//Function Macors
#define In32 Xil_In32
#define In16 Xil_In16
#define In8 Xil_In8

#define Out32 Xil_Out32
#define Out16 Xil_Out16
#define Out8 Xil_Out8

#define Reg32 *(volatile u32 *)
#define Reg16 *(volatile u16 *)
#define Reg8 *(volatile u8 *)


#define ASSERT(...) ({ if ((__VA_ARGS__)!=XST_SUCCESS) { return XST_FAILURE; } })

#define PRINT(...) \
    ({ \
        while (In8(PRINT_MUTEX_ADDR)) {} \
        Out8(PRINT_MUTEX_ADDR, 1); \
        xil_printf(__VA_ARGS__); \
        Out8(PRINT_MUTEX_ADDR, 0); \
    })


