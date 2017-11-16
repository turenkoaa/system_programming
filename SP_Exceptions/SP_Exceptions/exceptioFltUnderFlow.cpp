void exceptionFltStackChech()
{
	_try
	{
		RaiseException(EXCEPTION_FLT_UNDERFLOW, EXCEPTION_NONCONTINUABLE, 0, NULL);
	}
	_except(EXCEPTION_EXECUTE_HANDLER)
	{
		DWORD exceptionCode = GetExceptionCode(); 

		if (exceptionCode == EXCEPTION_FLT_UNDERFLOW)
			cout << "Code of EXCEPTION_FLT_UNDERFLOW: " << exceptionCode << endl;
		else
			cout << "Exception code: " << exceptionCode << endl;
	}

	return;
}