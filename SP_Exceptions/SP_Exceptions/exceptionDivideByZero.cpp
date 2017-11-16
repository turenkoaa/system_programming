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
		DWORD exceptionCode = GetExceptionCode(); // получаем код исключения 

		if (exceptionCode == EXCEPTION_INT_DIVIDE_BY_ZERO)
			cout << "Code of EXCEPTION_INT_DIVIDE_BY_ZERO: " << exceptionCode << endl;
		else
			cout << "Exception code: " << exceptionCode << endl;
	}
	return;
}