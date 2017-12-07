#include "stdafx.h"
#include <windows.h>
#include <iostream>
using namespace std;

EXCEPTION_RECORD exceptionRecord;
DWORD infoFilterForZeroDivider(EXCEPTION_POINTERS *p)
{
	exceptionRecord = *(p->ExceptionRecord);
	return EXCEPTION_EXECUTE_HANDLER;
}

void informationAboutException(_In_ DWORD dwExceptionCode,
	_In_ DWORD dwExceptionFlags,
	_In_ DWORD nNumberOfArguments,
	_In_reads_opt_(nNumberOfArguments) CONST ULONG_PTR * lpArguments) {

	_try
	{
		RaiseException(dwExceptionCode, dwExceptionFlags, nNumberOfArguments, lpArguments);
	}
		_except(infoFilterForZeroDivider(GetExceptionInformation()))
	{
		cout << "ExceptionCode: " << exceptionRecord.ExceptionCode << endl;
		cout << "ExceptionFlags: " << exceptionRecord.ExceptionFlags << endl;
		cout << "ExceptionAddress: " << exceptionRecord.ExceptionAddress << endl;
		cout << "NumberParameters: " << exceptionRecord.NumberParameters << endl;
		cout << "ExceptionRecord: " << exceptionRecord.ExceptionRecord << endl;

		if (exceptionRecord.ExceptionCode == dwExceptionCode)
		{
			cout << "Type of access: " << exceptionRecord.ExceptionInformation[0] << endl;
			cout << "Address of access: " << exceptionRecord.ExceptionInformation[1] << endl;
		}
		cout << endl;
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
		cout << "Information about EXCEPTION_INT_DIVIDE_BY_ZERO:\n";
		informationAboutException(EXCEPTION_INT_DIVIDE_BY_ZERO, 0, 0, NULL);
		break;
	case 2:
		cout << "Information about EXCEPTION_FLT_INVALID_OPERATION:\n";
		informationAboutException(EXCEPTION_FLT_INVALID_OPERATION, EXCEPTION_NONCONTINUABLE, 0, NULL);
		break;
	default:
		break;
	}
	system("pause");
	return 0;
}