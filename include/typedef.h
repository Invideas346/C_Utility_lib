#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include <stdint.h>

#define FALSE (uint8_t) 0
#define TRUE  (uint8_t) 1

// 0xffffffff could be reached but is extremely unlikely.
#define INDEX_NOTFOUND 0xffffffff

#endif  // __TYPEDEF_H__