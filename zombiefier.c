/* SJSU CMPE 142-02: Operating Systems
*  Nickolas Schiffer #012279319
*  PP #1: Creating Zombie Processes
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define TOPSCRIPT "ps aux | awk \'\"[Zz]\" ~ $8 { printf(\"%s, PID = %d\\n\", $8, $2); }\'"
int main(int argc, char *argv[]) 
{ 
     if (argc != 3){
         printf("Incorrect Format.\nUsage: zombifier -n [numZombies].\n");
         return EXIT_FAILURE;
     }
     if (strcmp(argv[1],"-n") != 0){
         printf("Incorrect tag Format.\nUsage: zombifier -n [numZombies].\n");
         return EXIT_FAILURE;
     }
     int numZombies = atoi(argv[2]);
     if ((numZombies <= 0)){
         printf("Only a positive number of zombies is allowed.\n");
         return EXIT_FAILURE;
     }
     printf("%d Zombies Requested.\n\n", numZombies);
    
    for (int i = 0; i < numZombies; i++){
        pid_t pid = fork();
        if (pid > 0){
            printf("parent PID: %d\n", getpid());
            sleep(1);
        }
        else if (pid == 0){
            printf("child  PID: %d\n\n", getpid());
            exit(0);
        }
        else {
            printf("Something went wrong. Exiting...\n");
            return EXIT_FAILURE;
        }
    }
    printf("Press t to view top zombies output or e to exit.\n\n");
    char c = getchar();
    if (c == 't'){system(TOPSCRIPT);}
    printf("\nZombies killed, exiting.\n");

	return EXIT_SUCCESS; 
}