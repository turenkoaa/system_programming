#include "stdafx.h"
#include <windows.h>
#include <iostream>
using namespace std;


LONG newFilter(PEXCEPTION_POINTERS pExceptionInfo)
{
	cout << "Set new filter-function." << endl;
	cout << "Exception code: " << pExceptionInfo->ExceptionRecord->ExceptionCode << endl;
	return EXCEPTION_EXECUTE_HANDLER;
}

void setNewFunctionFilter()
{
	LPTOP_LEVEL_EXCEPTION_FILTER oldFilter = SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)newFilter);
	cout << "Old filter-function address:" << oldFilter << endl;

	RaiseException(EXCEPTION_INT_DIVIDE_BY_ZERO, 0, 0, NULL);
	return;

}

int main()
{
	setNewFunctionFilter();

	return 0;
}
