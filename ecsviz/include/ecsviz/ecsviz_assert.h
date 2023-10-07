#pragma once
#include <stdint.h>


int ecsviz_assert_(
	const char *expr, 
	const char *file, 
	int32_t line, 
	const char *fn, 
	const char *fmt, 
	...
	);


#define ecsviz_assert(expr, ...) ((expr) ? 0: ecsviz_assert_ (#expr, __FILE__, __LINE__, __func__, __VA_ARGS__))
#define ecsviz_assert_notnull(expr) ecsviz_assert(expr, "")