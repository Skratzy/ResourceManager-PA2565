#pragma once

#include <assert.h>
#include <malloc.h>
#include <iostream>
#include <new>

#define RM_ASSERT(s) assert(s)
/*
	s: Size in bytes
*/
#define RM_MALLOC(s) malloc(s)
/*
	s: Type
*/
#define RM_NEW(s) new(RM_MALLOC(sizeof(s))) s
#define RM_FREE(s) free(s)
/*
	s: Debug message - to be printed
	l: Severity level
		0 -> print the message
		1 -> print the message and abort
*/
#define RM_DEBUG_MESSAGE(s, l) { \
	switch(l) { \
	case 0: std::cerr << s << std::endl; break; \
	case 1: std::cerr << s; abort(); \
}}