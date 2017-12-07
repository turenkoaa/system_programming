#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <exception>
#include <stdexcept>


using namespace std;

class MyException: public std::exception
{
public:
    explicit MyException(const char* message):
      msg_(message)
      {}

    explicit MyException(const std::string& message):
      msg_(message)
      {}

    virtual ~MyException() throw ()
    {}

    virtual const char* what() const throw (){
       return msg_.c_str();
    }
protected:
    std::string msg_;
};

class DBZException 
{
	public: DBZException() 
	{}
};

int main(int argc, char *argv[]){
	try {
		try {
			try {
				throw DBZException();
			}
			catch (int){}
		}
		catch (DBZException err){
			printf("DBZException was handled\n");
			throw MyException("MyException was handled.");
		}
	}
	catch (MyException err) {
		cout << err.what();
	}
	return 0;
}