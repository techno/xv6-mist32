#include <stddef.h>
#include <stdint.h>

// mist32 Flash MMU

#define FLASHMMU_START_ADDR 0x80000000
#define FLASHMMU_AREA_SIZE (					     \
  FLASHMMU_PAGEBUF_SIZE						     \
  + FLASHMMU_OBJCACHE_SIZE					     \
  + FLASHMMU_OBJ_MAX * sizeof(FLASHMMU_Object))

// 256MB Total
#define FLASHMMU_SIZE 0x10000000
#define FLASHMMU_PAGE_SIZE 0x1000
#define FLASHMMU_OBJ_MAX (FLASHMMU_SIZE / FLASHMMU_PAGE_SIZE)

// 4MB Page Buffer
#define FLASHMMU_PAGEBUF_SIZE 0x00400000
#define FLASHMMU_PAGEBUF_MAX (FLASHMMU_PAGEBUF_SIZE >> 12)
#define FLASHMMU_PAGEBUF_ADDR (FLASHMMU_START_ADDR)

// 16MB RAM Object Cache
#define FLASHMMU_OBJCACHE_SIZE 0x01000000
#define FLASHMMU_OBJCACHE_ADDR (FLASHMMU_START_ADDR + FLASHMMU_PAGEBUF_SIZE)

// FLAGS
#define FLASHMMU_FLAGS_VALID 0x1
#define FLASHMMU_FLAGS_OBJCACHE 0x2
#define FLASHMMU_FLAGS_PAGEBUF 0x4
#define FLASHMMU_FLAGS_ACCESS 0x8
#define FLASHMMU_FLAGS_DIRTY 0x10
#define FLASHMMU_FLAGS_DIRTYBUF 0x20 /* FIXME: dirtybuf flag should have pagebuf tag. */

#define FLASHMMU_OBJID(paddr) ((paddr) >> 12)
#define FLASHMMU_OFFSET(paddr) ((paddr) & 0xfff)
#define FLASHMMU_ADDR(objid) ((objid) << 12)
#define FLASHMMU_SECTOR(objid) (((objid) << 12) >> 9)
#define FLASHMMU_BLOCKS(size) (((size) + 511) >> 9)

struct flashmmu_object
{
  uint16_t size;
  volatile uint16_t flags;
  uint32_t cache_offset;
};

struct flashmmu_pool
{
  struct flashmmu_pool *next;
  union {
    void *p;
    uint objid;
  };
};

void omap_init(void);
uint omap_objalloc(int size);
void omap_objfree(uint objid);
void omap_pgfault(uint objid);