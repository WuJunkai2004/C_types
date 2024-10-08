#ifndef __C_TYPES_HEADER__
#define __C_TYPES_HEADER__

typedef char int8;
typedef unsigned char uint8;

typedef short int int16;
typedef unsigned short int uint16;

typedef int int32;
typedef unsigned int uint32;

typedef long long int64;
typedef unsigned long long uint64;

typedef int bool;
#define true 1
#define false 0

#ifndef __STR_HEADER__
#include "str.h"
#endif


#ifndef __LIST_HEADER__
#include "list.h"
#endif


#ifndef __MAPPING_HEADER__
#include "mapping.h"
#endif

#ifndef __CONTAINER_HEADER__
#include "container.h"
#endif

#ifdef LOAD_C_TYPES_SRC
#include "../src/str.c"
#include "../src/list.c"
#include "../src/mapping.c"
#include "../src/container.c"
#endif

#ifdef LOAD_C_TYPES_ITER
#include "iterator.h"
#endif

#endif
