#include "lab4.h"

int main()
{
    //run the shell until EOF (keyboard Ctrl+D) is detected
    while (userinput( ) != EOF)
    {
        process();
    }
    return 0;
}

//Bug fix 1:  In the process.c file I set 'int narg = 0' on line 11 when it was initiazlied because without it being initiazlied, the arguments from the previous user input were still being stored in the 'arg' array and were never erased.  The Kernel was not recognizing the second instance of the 'ls' command because it believed that it was a file or directory that wasn't there, so now narg correctly counts the number of arguments.

//Bug fix 2:  In runcommand.c file I added an if statement for when the cd command is used because we still want to use excevp in our code but that is for a change in environment so we need to use chdir and getenv for a change in directory in a separate if statement. On line 41 the function checks if the first 'word' in the user's argument is 'cd' using the strcmp function which compares two strings.  If it is true then it checks if the second argument is either NULL or the user inputted a 'word'.  If it is not NULL then the system changes the directory to the directory given using the chdir function.  If it is NULL then the program uses the getenv function to locate the path to the HOME directory and then calls chdir on the path to change to that location. The '..' command is build-in so it works automatically for 'cd ..' to move back out of a directory. In the switch statement for 'case 0', if the user was in the child process and the argument 'cd' was inputted, the program would exit the child process and move to the parent process to execute the cd command.

//Bug fix 3:  Similar to the previous fix, in the runcommand.c file I had an if statement that use the strcmp function to compare two strings at the top of the program.  If the user's first argument was the word 'exit' the function would terminate from exit(0).  I also had to include this in the swtich statement for 'case 0' if the user inputted 'exit' while they were in the child process the program would exit and move to the parent process to execute the exit. This was a simple fix to do.

//Bug fix 4:  At the top of the process.c file I added a handler function to catch the signal when SIGINT (Ctrl+C) was sent from the keyboard. On line 14 I added the signal call for if SIGINT or '^C' was inputted, it would send the signal to the handler function outside of the process function.  In the runcommand.c file in the switch statement for case 0, I added an if statement to check if it was in the child process and if it was and the '^C' command was inputted, it would send a signal to the handler to terminate that process but not exit the terminal.

//Bug fix 5:  In the runcommand.c file, I changed if(where == BACKGROUND) to if(where == FOREGROUND) and inside that if statement I had another if statement that would return -1 if the child process had terminated and was reieved but wasn't reaped so there was some sort of problem, otherwise it would return the pid of the terminated child.

