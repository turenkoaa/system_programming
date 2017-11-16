#include "stdafx.h"
#include <iostream>

#include <stdio.h>  
#include <eh.h>  
#include <windows.h>  

using namespace std;

class MySEException {
private:
	MySEException() {}
	unsigned int nSE;

public:
	MySEException(MySEException& e) : nSE(e.nSE) {}
	MySEException(unsigned int n) : nSE(n) {}
	~MySEException() {}
	unsigned int getSeNumber() { return nSE; }
};

void transFunction(unsigned int u, _EXCEPTION_POINTERS* pExp) {
	cout << "In se translator setter.\n";
	throw MySEException(u);
}

void zero(int a, int b) {
	int c = a / b;
}

void SEFunc() {
	__try {
		//zero(0, 0);
		//RaiseException(EXCEPTION_INT_DIVIDE_BY_ZERO, 0, 0, NULL);
	}
	__finally {
		printf_s("In finally\n");
	}
}

int main() {
	int x, y = 0;
	_set_se_translator(transFunction);
	try {
		RaiseException(EXCEPTION_INT_DIVIDE_BY_ZERO, 0, 0, NULL);
	}
	catch (MySEException e) {
		cout << "Got MySEException.\nnSE = " << e.getSeNumber();
	}

	return 0;
}
