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
void SigHandler(int sig){
	sigset_t sigset;
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGFPE);
	sigaddset(&sigset, SIGTERM);

	sigprocmask(SIG_BLOCK, &sigset, NULL);

	switch (sig) {
		case SIGFPE:
			printf("FPE signal has been handled. Code: %i\n", sig);
			GenerateTERMException();
			break;
		case SIGTERM:
			printf("TERM signal has been handled. Code: %i\n", sig);
			GenerateDBZException();
			break;
	}
	exit(EXIT_FAILURE);

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
	if (signal(SIGFPE, SigHandler) == SIG_ERR)
		printf("Cant set SIGFPE handler\n");
	
	if (signal(SIGTERM, SigHandler) == SIG_ERR)
		printf("Cant set SIGTERM handler\n");
	
	if (argc == 2) {
		if (strcmp(argv[1], "-1") == 0)
			GenerateDBZException();
		else if (strcmp(argv[1], "-2") == 0) {
			GenerateTERMException();
		}
	}
	return 0;
}