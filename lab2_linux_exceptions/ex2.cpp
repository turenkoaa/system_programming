#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <cstring>
#include <syslog.h>
void GenerateDBZException() {
	raise(8);
}
void GenerateTERMException() {
	raise(15);
}
void SigFPEHandler(int sig){
	openlog("ex2", 0, LOG_USER);
	syslog(LOG_NOTICE, "FPE signal occured! Code: %i\n", sig);
	closelog();
	printf("FPE signal has been handled. Code: %i\n", sig);
	exit(EXIT_FAILURE);

}
void SigTERMHandler(int sig){
	openlog("ex2", 0, LOG_USER);
	syslog(LOG_NOTICE, "TERM signal occured! Code: %i\n", sig);
	closelog();
	printf("TERM signal has been handled. Code: %i\n", sig);
	exit(EXIT_FAILURE);

}
int main(int argc, char *argv[]){
	if (signal(SIGFPE, SigFPEHandler) == SIG_ERR)
		printf("Cant set SIGFPE handler\n");
	if (signal(SIGTERM, SigTERMHandler) == SIG_ERR)
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