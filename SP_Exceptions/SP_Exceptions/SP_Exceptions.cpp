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

void exceptionHeandlerSearch()
{
	_try
	{
		RaiseException(EXCEPTION_FLT_INVALID_OPERATION, EXCEPTION_NONCONTINUABLE, 0, NULL);
	}
	_except((GetExceptionCode() == EXCEPTION_FLT_INVALID_OPERATION)
					? EXCEPTION_EXECUTE_HANDLER
					: EXCEPTION_CONTINUE_SEARCH)
	{
		cout << "Got an EXCEPTION_FLT_INVALID_OPERATION" << endl;
	}

	_try
	{
		RaiseException(EXCEPTION_INT_DIVIDE_BY_ZERO, 0, 0, NULL);
	}
		_except((GetExceptionCode() == EXCEPTION_INT_DIVIDE_BY_ZERO)
			? EXCEPTION_EXECUTE_HANDLER
			: EXCEPTION_CONTINUE_SEARCH)
	{
		cout << "Got an EXCEPTION_INT_DIVIDE_BY_ZERO" << endl;
	}

	return;
}

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

void nestedTryExceptBlock() {
	_try
	{
		_try
		{
			RaiseException(EXCEPTION_INT_DIVIDE_BY_ZERO, 0, 0, NULL);
		}
		_except(GetExceptionCode() == EXCEPTION_INT_DIVIDE_BY_ZERO 
			? EXCEPTION_EXECUTE_HANDLER 
			: EXCEPTION_CONTINUE_SEARCH)
		{
			cout << "Internal Block.\nException EXCEPTION_INT_DIVIDE_BY_ZERO." << endl;
		}

		_try
		{
			RaiseException(EXCEPTION_FLT_INVALID_OPERATION, 0, 0, NULL);
		}
		_except(GetExceptionCode() == EXCEPTION_FLT_OVERFLOW 
			? EXCEPTION_EXECUTE_HANDLER 
			: EXCEPTION_CONTINUE_SEARCH)
		{
			cout << "Internal Block.\nException EXCEPTION_FLT_OVERFLOW." << endl;
		}
	}
	_except(GetExceptionCode() == EXCEPTION_FLT_INVALID_OPERATION ?
			EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		cout << "External block.\nException EXCEPTION_FLT_INVALID_OPERATION." << endl;
	}
	return;

}

void breakWithGoto() {
	_try
	{
		cout << "Try block start." << endl;
		goto afterExit;
		RaiseException(EXCEPTION_FLT_INVALID_OPERATION, 0, 0, NULL);
		cout << "Try block end." << endl;
		
	}
		_except(EXCEPTION_EXECUTE_HANDLER)
	{
		cout << "Exception was handeled." << endl;
	}


afterExit: 
	cout << "Try block end with goto." << endl;
	return;

}

void breakWithLeave() {
	_try
	{
		cout << "Try block start." << endl;
		_leave;
		RaiseException(EXCEPTION_FLT_INVALID_OPERATION, 0, 0, NULL);
		cout << "Try block end." << endl;

	}
	_except(EXCEPTION_EXECUTE_HANDLER)
	{
		cout << "Exception was handeled." << endl;
	}
	cout << "Do smth after try." << endl;
	return;

}

void useFinallyBlock() {
	_try
	{
		RaiseException(EXCEPTION_FLT_INVALID_OPERATION, 0, 0, NULL);
		cout << "Do smth after exception.\n";
	}
	_finally
	{
		cout << "In finally block do smth.";
	}
	return;
}

void useAbnormalTerminationForCheckTryBlock() {
	_try
	{
		sqrt(-50);
		goto exit;
	}
	_finally
	{
		if (!AbnormalTermination())
			cout << "Termination was normal." << endl;
		else
			cout << "Termination wan`t normal." << endl;
	}

	exit:
	return;
}

int main()
{
	//exceptionDivideByZero();
	//exceptionFltInvalid();

	//exceptionHeandlerSearch();

	//useSpecialFilterForZeroDivider();
	//useSpecialFilterForFltInvalid();

	//cout << "Information about EXCEPTION_INT_DIVIDE_BY_ZERO:\n";
	//informationAboutException(EXCEPTION_INT_DIVIDE_BY_ZERO, 0, 0, NULL);
	//cout << "Information about EXCEPTION_FLT_INVALID_OPERATION:\n";
	//informationAboutException(EXCEPTION_FLT_INVALID_OPERATION, EXCEPTION_NONCONTINUABLE, 0, NULL);

	//setNewFunctionFilter();

	//nestedTryExceptBlock();

	//breakWithGoto();
	//breakWithLeave();

	useFinallyBlock();

	//useAbnormalTerminationForCheckTryBlock();

	return 0;
}
