/*
SDL2 depends on __iob_func, which is replaced by __acrt_iob_func in vs 2015
the two are differing types and dynamically linked,
thus #define __iob_func __acrt_iob_func will not work
*/
#if _MSC_VER >= 1900 
#include <stdio.h>
FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __iob_func(void)
{
	return _iob;
}
#endif