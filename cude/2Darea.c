#include <stdio.h>
#include <sys/types.h>
#include <time.h>

typedef unsigned int u32_t;
typedef unsigned short ut16_t;
typedef unsigned char u8_t;
typedef unsigned long u64_t;

typedef signed char s8_t;
typedef signed short s16_t;
typedef signed int s32_t;
typedef signed long s64_t;

typedef struct {
  s64_t x, y, z;
  s64_t nx, ny, nz;
  s64_t tx, ty;
} WorldPos;

typedef struct {
  u32_t v1;
  u32_t v2;
} WorldEdge;

typedef struct {
  u32_t v1;
  u32_t v2;
  u32_t v3;
};

static u32_t timeshamp;
