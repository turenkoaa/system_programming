#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <cstring>
void GenerateDBZException() {
	raise(8);
}
void GenerateTERMException() {
	raise(15);
}
void SigFPEHandler(int sig){
	printf("FPE signal has been handled. Code: %i\n", sig);
	GenerateTERMException();
	exit(EXIT_FAILURE);

}
void SigTERMHandler(int sig){
	printf("TERM signal has been handled. Code: %i\n", sig);
	exit(EXIT_FAILURE);

}
int main(int argc, char *argv[]){
	if (signal(SIGFPE, SigFPEHandler) == SIG_ERR)
		printf("Cant set SIGFPE handler\n");
	if (signal(SIGTERM, SigTERMHandler) == SIG_ERR)
		printf("Cant set SIGTERM handler\n");
	GenerateDBZException();
	return 0;
}