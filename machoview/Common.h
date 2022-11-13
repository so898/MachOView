/*
 *  Common.h
 *  MachOView
 *
 *  Created by Peter Saghelyi on 10/09/2011.
 *
 */


//#define MV_NO_MULTITHREAD
//#define MV_NO_ARCHIVER
//#define MV_STATISTICS

extern NSCondition * pipeCondition;
extern int32_t numIOThread;
extern int64_t nrow_total;  // number of rows (loaded and empty)
extern int64_t nrow_loaded; // number of loaded rows

#define NSSTRING(C_STR) [NSString stringWithCString: (char *)(C_STR) encoding: [NSString defaultCStringEncoding]]
#define CSTRING(NS_STR) [(NS_STR) cStringUsingEncoding: [NSString defaultCStringEncoding]]

#define N_ELEMENTS(ARR)   (sizeof(ARR)/sizeof(*(ARR)))
#define FIRST_ELEM(ARR)   (&(ARR)[0])
#define LAST_ELEM(ARR)    (&(ARR)[N_ELEMENTS(ARR)-1])

#if defined (__i386__) || defined (__x86_64__)
#else

struct x86_state_hdr {
    uint32_t        flavor;
    uint32_t        count;
};
typedef struct x86_state_hdr x86_state_hdr_t;

struct x86_thread_state32_t
{
    unsigned int    __eax;
    unsigned int    __ebx;
    unsigned int    __ecx;
    unsigned int    __edx;
    unsigned int    __edi;
    unsigned int    __esi;
    unsigned int    __ebp;
    unsigned int    __esp;
    unsigned int    __ss;
    unsigned int    __eflags;
    unsigned int    __eip;
    unsigned int    __cs;
    unsigned int    __ds;
    unsigned int    __es;
    unsigned int    __fs;
    unsigned int    __gs;
};

struct x86_thread_state64_t
{
    __uint64_t    __rax;
    __uint64_t    __rbx;
    __uint64_t    __rcx;
    __uint64_t    __rdx;
    __uint64_t    __rdi;
    __uint64_t    __rsi;
    __uint64_t    __rbp;
    __uint64_t    __rsp;
    __uint64_t    __r8;
    __uint64_t    __r9;
    __uint64_t    __r10;
    __uint64_t    __r11;
    __uint64_t    __r12;
    __uint64_t    __r13;
    __uint64_t    __r14;
    __uint64_t    __r15;
    __uint64_t    __rip;
    __uint64_t    __rflags;
    __uint64_t    __cs;
    __uint64_t    __fs;
    __uint64_t    __gs;
};

struct x86_thread_state {
    x86_state_hdr_t                 tsh;
    union {
        x86_thread_state32_t        ts32;
        x86_thread_state64_t        ts64;
    } uts;
};

/*
 * THREAD_STATE_FLAVOR_LIST 0
 *      these are the supported flavors
 */
#define x86_THREAD_STATE32              1
#define x86_FLOAT_STATE32               2
#define x86_EXCEPTION_STATE32           3
#define x86_THREAD_STATE64              4
#define x86_FLOAT_STATE64               5
#define x86_EXCEPTION_STATE64           6
#define x86_THREAD_STATE                7
#define x86_FLOAT_STATE                 8
#define x86_EXCEPTION_STATE             9
#define x86_DEBUG_STATE32               10
#define x86_DEBUG_STATE64               11
#define x86_DEBUG_STATE                 12
#define THREAD_STATE_NONE               13
/* 14 and 15 are used for the internal x86_SAVED_STATE flavours */
/* Arrange for flavors to take sequential values, 32-bit, 64-bit, non-specific */
#define x86_AVX_STATE32                 16
#define x86_AVX_STATE64                 (x86_AVX_STATE32 + 1)
#define x86_AVX_STATE                   (x86_AVX_STATE32 + 2)
#define x86_AVX512_STATE32              19
#define x86_AVX512_STATE64              (x86_AVX512_STATE32 + 1)
#define x86_AVX512_STATE                (x86_AVX512_STATE32 + 2)
#define x86_PAGEIN_STATE                22
#define x86_THREAD_FULL_STATE64         23
#define x86_INSTRUCTION_STATE           24
#define x86_LAST_BRANCH_STATE           25

#endif
