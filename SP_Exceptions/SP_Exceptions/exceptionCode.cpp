#include "stdafx.h"
#include <windows.h>
#include <iostream>
using namespace std;

void exceptionDivideByZero()
{
	_try
	{
		RaiseException(
			EXCEPTION_INT_DIVIDE_BY_ZERO,            // dwExceptionCode
			0,                     // dwExceptionFlags, 0 indicate a continuable exception
			0,					   // nNumberOfArguments 
			NULL);
	}
		_except(EXCEPTION_EXECUTE_HANDLER)
	{
		DWORD exceptionCode = GetExceptionCode();

		if (exceptionCode == EXCEPTION_INT_DIVIDE_BY_ZERO)
			cout << "Code of EXCEPTION_INT_DIVIDE_BY_ZERO: " << exceptionCode << endl;
		else
			cout << "Exception code: " << exceptionCode << endl;
	}
	return;
}

void exceptionFltInvalid()
{
	_try
	{
		RaiseException(EXCEPTION_FLT_INVALID_OPERATION, EXCEPTION_NONCONTINUABLE, 0, NULL);
	}
		_except(EXCEPTION_EXECUTE_HANDLER)
	{
		DWORD exceptionCode = GetExceptionCode();

		if (exceptionCode == EXCEPTION_FLT_INVALID_OPERATION)
			cout << "Code of EXCEPTION_FLT_INVALID_OPERATION: " << exceptionCode << endl;
		else
			cout << "Exception code: " << exceptionCode << endl;
	}

	return;
}

int main(int argc, char *argv[])
{
	int exc = 0;
	exc = atoi(argv[1]);
	cout << "Getting exception code\n1 - INT_DIVISION_BY_ZERO\n2 -  EXCEPTION_FLT_INVALID_OPERATION" <<
		endl;
	cout << exc << " has been chosen" << endl;
	switch (exc)
	{
	case 1:
		cout << "method exceptionDivideByZero() will generate INT_DIVISION_BY_ZERO" << endl;
		exceptionDivideByZero();
		break;
	case 2:
		cout << "method exceptionFltInvalid() will generate  EXCEPTION_FLT_INVALID_OPERATION" << endl;
		exceptionFltInvalid();
		break;
	default:
		break;
	}
	system("pause");
	return 0;
}