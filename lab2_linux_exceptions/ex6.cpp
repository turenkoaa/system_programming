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
		if (argc == 2) {
			if (strcmp(argv[1], "-1") == 0){
				throw MyException("MyException was handled.");
			}
			else if (strcmp(argv[1], "-2") == 0) {
				throw DBZException();
			}
		}
	}
	catch (MyException err){
		cout << err.what();
	}
	catch (DBZException err) {
		printf("DBZException was handled\n");
	}
	return 0;
}