#include "stdafx.h"
#include <windows.h>
#include <iostream>
using namespace std;

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
	useAbnormalTerminationForCheckTryBlock();
	return 0;
}
