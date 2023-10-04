#include "ecsviz_assert.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ecsviz_abort()
{
	abort();
}

int ecsviz_assert_(
	const char *expr, 
	const char *file, 
	int32_t line, 
	const char *fn, 
	const char *fmt, 
	...
	)
{
	va_list args;
	va_start(args, fmt);
	int r = vprintf(fmt, args);
	va_end(args);
	ecsviz_abort();
	return r;
}