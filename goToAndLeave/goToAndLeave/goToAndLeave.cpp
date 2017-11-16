#include "stdafx.h"
#include <windows.h>
#include <iostream>
using namespace std;

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


int main()
{
	breakWithGoto();
	breakWithLeave();

	system("pause");
	return 0;
}
