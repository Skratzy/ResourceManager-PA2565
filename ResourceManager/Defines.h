#pragma once

#include <assert.h>
#include <malloc.h>

#define RM_ASSERT(s) assert(s)
#define RM_MALLOC(s) malloc(s)
#define RM_FREE(s) free(s)