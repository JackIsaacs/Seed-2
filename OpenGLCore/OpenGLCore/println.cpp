#include "println.h"



void println(char const* const _Format, ...)
{
	va_list _ArgList;
	__crt_va_start(_ArgList, _Format);
	_vfprintf_l(stdout, _Format, NULL, _ArgList);
	__crt_va_end(_ArgList);

	printf("\n");
}
