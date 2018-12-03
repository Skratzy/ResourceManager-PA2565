#pragma once

#include <assert.h>
#include <malloc.h>
#include <iostream>

#define RM_ASSERT(s) assert(s)
#define RM_MALLOC(s) malloc(s)
#define RM_FREE(s) free(s)
/*
	s: Debug message - to be printed
	l: Severity level - higher => more sever
*/
#define RM_DEBUG_MESSAGE(s, l) { \
	switch(l) { \
	case 0: std::cout << s << std::endl; break; \
	case 1: std::cerr << s; abort(); \
}}