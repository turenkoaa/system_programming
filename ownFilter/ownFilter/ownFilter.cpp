#define _CRT_SECURE_NO_WARNINGS


#include "stdafx.h"
#include <windows.h>
#include <iostream>
using namespace std;

DWORD specialFilterForZeroDivider(DWORD exceptionCode, int &divider, int &newDivider)
{
	if (exceptionCode == EXCEPTION_INT_DIVIDE_BY_ZERO)
	{
		cout << "Got an EXCEPTION_INT_DIVIDE_BY_ZERO." << endl;
		divider = newDivider;
		cout << "Set new divider = " << divider << " and continue." << endl;
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	else
		return EXCEPTION_EXECUTE_HANDLER;
}

void useSpecialFilterForZeroDivider() {
	int a = 100;
	int b = 0;
	int newb = 2;

	_try
	{
		if (b == 0) {
			RaiseException(EXCEPTION_INT_DIVIDE_BY_ZERO, 0, 0, NULL);
		}
	a = a / b;
	cout << "Success a = " << a << endl;
	}
		_except(specialFilterForZeroDivider(GetExceptionCode(), b, newb))
	{
		cout << "Exception code: " << GetExceptionCode() << endl;
	}
}

DWORD specialFilterForFltInvalid(DWORD exceptionCode, double &square)
{
	if (exceptionCode == EXCEPTION_FLT_INVALID_OPERATION)
	{
		cout << "Got an EXCEPTION_FLT_INVALID_OPERATION" << endl;
		square = -square;
		cout << "Set new square = " << square << " and continue." << endl;

		_clearfp();

		return EXCEPTION_CONTINUE_EXECUTION;
	}
	else
		return EXCEPTION_EXECUTE_HANDLER;
}

void useSpecialFilterForFltInvalid() {
	double a = -15.98998;
	DWORD FPOld = _controlfp(0, 0);
	DWORD FPNew = FPOld & ~(EM_OVERFLOW | EM_UNDERFLOW | EM_INEXACT | EM_ZERODIVIDE | EM_DENORMAL | EM_INVALID);
	_controlfp(FPNew, MCW_EM);
	_try
	{
		a = sqrt(a);
	cout << "Success.";
	}
		_except(specialFilterForFltInvalid(GetExceptionCode(), a))
	{
		cout << "Exception code: " << GetExceptionCode() << endl;
		_clearfp();
	}
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
		cout << "method useSpecialFilterForZeroDivider():" << endl;
		useSpecialFilterForZeroDivider();
		break;
	case 2:
		cout << " useSpecialFilterForFltInvalid() will generate  EXCEPTION_FLT_INVALID_OPERATION" << endl;
		useSpecialFilterForFltInvalid();
		break;
	default:
		break;
	}
	system("pause");
	return 0;
}