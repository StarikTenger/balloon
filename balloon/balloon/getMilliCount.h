#pragma once
#include <cstdlib>
#include <sys/timeb.h>
using namespace std;
int getMilliCount() {
	timeb tb;
	ftime(&tb);
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}