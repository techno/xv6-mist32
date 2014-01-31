// Memory layout

#define EXTMEM  0x100000            // Start of extended memory
#define PHYSTOP 0x8000000           // Top physical memory
#define DEVSPACE 0xFE000000         // Other devices are at high addresses

#define FMMUSTART 0x80000000
#define FMMUPBEND (FMMUSTART + FLASHMMU_PAGEBUF_SIZE)
#define FMMUEND (FMMUSTART+0x10000000)
#define FMMUVIRT 0xa0000000
#define FMMUOBJC (FMMUVIRT + FLASHMMU_PAGEBUF_SIZE)

// Key addresses for address space layout (see kmap in vm.c for layout)
#define KERNBASE 0x80000000         // First kernel virtual address
#define KERNLINK (KERNBASE+EXTMEM)  // Address where kernel is linked

#ifndef __ASSEMBLER__

static inline uint v2p(void *a) { return ((uint) (a))  - KERNBASE; }
static inline void *p2v(uint a) { return (void *) ((a) + KERNBASE); }

#endif

#define V2P(a) (((uint) (a)) - KERNBASE)
#define P2V(a) (((void *) (a)) + KERNBASE)

#define V2P_WO(x) ((x) - KERNBASE)    // same as V2P, but without casts
#define P2V_WO(x) ((x) + KERNBASE)    // same as V2P, but without casts
