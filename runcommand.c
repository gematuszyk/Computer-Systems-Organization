#include "lab4.h"

void childhandler() {
        
        pid_t pid1;
        int status1;
    
        while(1) {
            pid1 = waitpid(pid1,&status1,WNOHONG);
            if(pid1 == 0) {
                return;
            }else if(pid == -1) {
                return;
            }
        }
}

// Execute a command with optional wait
int runcommand(char** cline, int where)
{
    pid_t pid;
    int status;
    char* path;
`
    signal(SIGCHLD, childhandler);

    if(strcmp(cline[0], "exit")==0) {
        exit(0);
    }
    else if(strcmp(cline[0], "cd")==0) {
        if(cline[1]!=NULL) {
            chdir(cline[1]);
        }
        else {
            path = getenv("HOME");
            chdir(path);
        }
    }
    else {
        switch(pid = fork())
        {
            case -1:
                perror(SHELL_NAME);
                return (-1);
            case 0:
                execvp(*cline,cline);
                //we should never get to this code, sice execve does not return
                perror(*cline);
                exit(1);
        }
    }
    // Code for parent
    // If background process print pid and exit program is running in the background
    if(where == BACKGROUND)
    {
        printf("[Process id %d]\n",pid);
        return 0;
    }

    // Wait until process pid exits
    if (waitpid(pid,&status,0) == -1) 
    {
        return -1;
    } 
    else 
    {
        return status;
    }
}
