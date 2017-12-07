#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <cstring>
#include <math.h>

void GenerateDBZException() {
   int a = 1;
   int b = a / (a - 1);
}
void GenerateTRMException() {
   raise(SIGTERM);
}
int main(int argc, char *argv[]){
   if (argc == 2) {
    if (strcmp(argv[1], "-DBZ") == 0)
        GenerateDBZException();
    else if (strcmp(argv[1], "-TRM") == 0) {
        GenerateTRMException();
    }
}
return 0;
}