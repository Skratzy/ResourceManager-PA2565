#ifndef _RM_DEFINES_
#define _RM_DEFINES_

#include <assert.h>
#include <malloc.h>
#include <iostream>
#include <new>
#include <windows.h>

#define RM_ASSERT(s) assert(s)
/*
	s: Size in bytes
*/
#define RM_MALLOC(s) malloc(s)
/*
	TYPE: Type
*/
#define RM_NEW(TYPE) new(RM_MALLOC(sizeof(TYPE))) TYPE
#define RM_FREE(s) free(s)
#define RM_DELETE(s) delete s
/*
	s: Debug message - to be printed
	l: Severity level
		0 -> print the message
		1 -> print the message and abort
*/
#define RM_DEBUG_MESSAGE(s, l) { \
	HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE); \
	CONSOLE_SCREEN_BUFFER_INFO conScrBufInf; \
	GetConsoleScreenBufferInfo(stdHandle, &conScrBufInf); \
	switch(l) { \
	case 0: \
		SetConsoleTextAttribute(stdHandle, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY); \
		std::cerr << "WARNING: " << s << std::endl; \
		SetConsoleTextAttribute(stdHandle, conScrBufInf.wAttributes); \
		break; \
	case 1:\
		SetConsoleTextAttribute(stdHandle, BACKGROUND_RED | BACKGROUND_INTENSITY);\
		std::cerr << "ERROR: " << s << std::endl;\
		SetConsoleTextAttribute(stdHandle, conScrBufInf.wAttributes);\
		abort();\
		break;\
	default: break;\
}}

#define HANDMADE_MATH_IMPLEMENTATION
#define HANDMADE_MATH_NO_SSE

#define SOKOL_LOG(s) RM_DEBUG_MESSAGE(s, 0)

#ifdef __cplusplus
extern "C" {
#include "Sokol/HandmadeMath.h"
#include "Sokol/sokol_gfx.h"
}
#endif

/* a uniform block with a model-view-projection matrix */
typedef struct {
	hmm_mat4 m;
	hmm_mat4 vp;
} vs_params_t;

#endif //_RM_DEFINES_