#ifndef __C_TYPES_HEADER__
#define __C_TYPES_HEADER__

typedef char int8;
typedef unsigned char uint8;

typedef int int32;
typedef unsigned int uint32;

typedef long long int64;
typedef unsigned long long uint64;

typedef int bool;
const bool true = 1;
const bool false = 0;

#ifndef __STR_HEADER__
#include "str.h"
#endif


#ifndef __LIST_HEADER__
#include "list.h"
#endif


#ifndef __MAPPING_HEADER__
#include "mapping.h"
#endif


#endif
