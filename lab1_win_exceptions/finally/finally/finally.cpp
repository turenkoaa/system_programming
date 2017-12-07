#include "stdafx.h"
#include <windows.h>
#include <iostream>
using namespace std;

void useFinallyBlock() {
	_try
	{
		RaiseException(EXCEPTION_INT_DIVIDE_BY_ZERO, 0, 0, NULL);
		cout << "Do smth after exception.\n";
	}
	_finally
	{
		cout << "In finally block do smth.";
	}
	return;
}


int main()
{
	useFinallyBlock();
    return 0;
}

