#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <cstring>

using namespace std;


void GenerateDBNException() {
	raise(8);
}
void GenerateTERMException() {
	raise(15);
}
void SigHandler(int sig, siginfo_t *info, void *context){
	switch (sig) {
		case SIGFPE:
		printf("FPE signal has been handled\n");
		break;
		case SIGTERM:
		printf("TERM signal has been handled\n");
		break;
	}
	 cout << "Signal number: " << info->si_signo << endl;
	 cout << "Errno: " << info->si_errno << endl;
	 cout << "Signal code: " << info->si_code << endl;
	 cout << "PID: " << info->si_pid << endl;
	 cout << "UID: " << info->si_uid << endl;
	 cout << "Status: " << info->si_status << endl;
	 cout << "User time: " << info->si_utime << endl;
	 cout << "System time: " << info->si_stime << endl;
	 cout << "Signal address: " << info->si_addr << endl;
	 cout << "Signal event: " << info->si_band << endl;
	exit(EXIT_FAILURE);

}

struct sigaction act, oact;

int main(int argc, char *argv[]){
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &SigHandler;

	if (argc == 2) {
		if (strcmp(argv[1], "-1") == 0){
			if (sigaction(SIGFPE, &act, &oact) == -1)
				printf("Cant set SIGFPE handler\n");
			GenerateDBNException();
		}
		else if (strcmp(argv[1], "-2") == 0) {
			if (sigaction(SIGTERM, &act, &oact) == -1)
				printf("Cant set SIGTERM handler\n");
			GenerateTERMException();
		}
	}
	return 0;
}