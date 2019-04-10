#include "Strassen_Vector.h"

int FindFaddingSize(const int n)
{
	if (!(n & (n - 1))) return 0;
	else if (n < 4)     return 4;
	else if (n < 16)    return 16;
	else if (n < 32)    return 32;
	else if (n < 64)    return 64;
	else if (n < 128)   return 128;
	else if (n < 256)   return 256;
	else                return 512;
}

