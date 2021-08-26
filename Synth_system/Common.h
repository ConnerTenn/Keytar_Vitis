

#include "xparameters.h"
#include "xil_types.h"
#include "xil_io.h"
#include "stdlib.h"

#include "xuartps.h"
#include "xil_printf.h"


#define SHARED_ADDR (0xFFFF0000)


//Function Macors
#define In32 Xil_In32
#define In16 Xil_In16
#define In8 Xil_In8

#define Out32 Xil_Out32
#define Out16 Xil_Out16
#define Out8 Xil_Out8

#define MEM32(addr) ((volatile u32 *)(addr))
#define MEM16(addr) ((volatile u16 *)(addr))
#define MEM8(addr) ((volatile u8 *)(addr))
#define REG32(reg) (*MEM32(reg))
#define REG16(reg) (*MEM16(reg))
#define REG8(reg) (*MEM8(reg))

#define ALIGN8 __attribute__ ((aligned(8)))
#define ALIGN16 __attribute__ ((aligned(16)))
#define ALIGN32 __attribute__ ((aligned(32)))
#define ALIGN64 __attribute__ ((aligned(64)))


#define REPEAT0(X)
#define REPEAT1(X) X
#define REPEAT2(X) REPEAT1(X) X
#define REPEAT3(X) REPEAT2(X) X
#define REPEAT4(X) REPEAT3(X) X
#define REPEAT5(X) REPEAT4(X) X
#define REPEAT6(X) REPEAT5(X) X
#define REPEAT7(X) REPEAT6(X) X
#define REPEAT8(X) REPEAT7(X) X
#define REPEAT9(X) REPEAT8(X) X
#define REPEAT10(X) REPEAT9(X) X

#define REPEAT(HUNDREDS,TENS,ONES,X) \
  REPEAT##HUNDREDS(REPEAT10(REPEAT10(X))) \
  REPEAT##TENS(REPEAT10(X)) \
  REPEAT##ONES(X)

#define sev() asm ("sev")
#define nop() asm volatile ("nop")


#define ASSERT(...) ({ if ((__VA_ARGS__)!=XST_SUCCESS) { return XST_FAILURE; } })


#define PRINT_MUTEX_OFF (0x0000)
#define PRINT_MUTEX_ADDR (SHARED_ADDR+PRINT_MUTEX_OFF)

#define PRINT_GETLOCK  \
    ({ \
        while (In8(PRINT_MUTEX_ADDR)) {} \
        Out8(PRINT_MUTEX_ADDR, 1); \
    })
#define PRINT_RELEASELOCK  \
    ({ \
        Out8(PRINT_MUTEX_ADDR, 0); \
    })
#define PRINT(...) \
    ({ \
        while (In8(PRINT_MUTEX_ADDR)) {} \
        Out8(PRINT_MUTEX_ADDR, 1); \
        xil_printf(__VA_ARGS__); \
        Out8(PRINT_MUTEX_ADDR, 0); \
    })
#define PRINT_NOLOCK(...) \
    ({ \
        xil_printf(__VA_ARGS__); \
    })

#define TERM_RESET   "\e[m"
#define TERM_BLACK   "\e[1;30m"
#define TERM_RED     "\e[1;31m"
#define TERM_GREEN   "\e[1;32m"
#define TERM_YELLOW  "\e[1;33m"
#define TERM_BLUE    "\e[1;34m"
#define TERM_MAGENTA "\e[1;35m"
#define TERM_CYAN    "\e[1;36m"
#define TERM_WHITE   "\e[1;37m"
#define TERM_UP      "\e[1F"

#define TERM_MOVE_UP(n)\
    ({ \
        PRINT_NOLOCK("\e[%dF", (n)); \
    })

