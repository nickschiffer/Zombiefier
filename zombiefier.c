/* SJSU CMPE 142-02: Operating Systems
*  Nickolas Schiffer #012279319
*  PP #1: Creating Zombie Processes
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#define PSSCRIPT "ps aux | awk \'\"[Zz]\" ~ $8 { printf(\"%s, PID = %d\\n\", $8, $2); }\'"

void sigcont_handler(int signum){
    printf("SIGCONT recieved for PID #%d\n",signum);
    exit(signum);
}

int main(int argc, char *argv[]) 
{    
     int parent_PID = 0;
     if (argc != 3){
         printf("Incorrect Format.\nUsage: zombiefier -n [numZombies].\n");
         return EXIT_FAILURE;
     }
     if (strcmp(argv[1],"-n") != 0){
         printf("Incorrect tag Format.\nUsage: zombiefier -n [numZombies].\n");
         return EXIT_FAILURE;
     }
     int numZombies = atoi(argv[2]);
     if ((numZombies <= 0)){
         printf("Only a positive number of zombies is allowed.\n");
         return EXIT_FAILURE;
     }
     printf("\n%d Zombies Requested.\n\n", numZombies);
    
    for (int i = 0; i < numZombies; i++){
        pid_t pid = fork();
        if (pid > 0){
            parent_PID = getpid();
            printf("parent PID: %d\n", parent_PID);
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
    printf("Zombie Processes from parent PID #%d via ps:\n\n", parent_PID);
    system(PSSCRIPT);
    signal(SIGCONT, sigcont_handler);
    printf("\nSend \"kill -SIGCONT %d\" in separate console window to kill Zombies.\n", parent_PID);
    while (1){
        sleep(1);
    }
    // printf("Press t to view ps zombies output or e to exit.\n\n");
    // char c = getchar();
    // if (c == 't'){system(PSSCRIPT);}
    // printf("\nZombies killed, exiting.\n");

	return EXIT_SUCCESS; 
}
