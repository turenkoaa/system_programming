#include "stdafx.h"
#include <windows.h>
#include <iostream>
using namespace std;

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


int main()
{
	nestedTryExceptBlock();

	return 0;
}
