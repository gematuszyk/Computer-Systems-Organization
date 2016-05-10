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

//Bug fix 1: In the process.c file I moved narg = 0 (line 14) which was after the two if-statement in the AMPERSAND case, into the first if statement after runcommand(arg, type) (line 37).  I did this because before it was resetting the number of arguments to 0 after 1 argument so the command 'cd Desktop' would only register the first argument 'cd'.  Moving it after runcommand(arg, type) resets the counter to be zero so every time a new command is passed, it correctly counts the number of arguments.

//Bug fix 2:  In the runcommand.c file I added an if statement for when the cd command is used because we still want to use excevp in our code but that is for a change in environment so need to use chdir and getenv for a change in directory in a separate if statement.  On line 16 the function checks if the first 'word' in the user's argument is 'cd' using the strcmp function which compares two strings.  If it is true then it checks if the second argument is either NULL or the user inputted a 'word'.  If it is not NULL then the system changes the directory to the directory given using the chdir function.  If it is NULL then the program uses the getenv function to locate the path to the HOME directory and then calls chdir on the path to change to that location.

//Bug fix 3:  Similar to the previous fix, in the runcommand.c file I had an if statement that uses the strcmp function to compare two strings at the top of the program.  If the user's first argument was the word 'exit' the function would terminate.  This was a simple fix.

//Bug fix 4:  At the top of the process.c file I added a handler function to catch the signal when SIGINT (Ctrl + C) was sent from the keyboard.  On line 14 I added the signal call for if SIGNIT or '^C' was inputted, it would send the signal to the handler function outside of the process function.

//Bug fix 5:  In the runcommand.c file of code 'if (waitpid(pid,&status,0) == -1)' is waiting for a specific child process to exit and if it has exited it will equal -1.  To reap the background processes, in this if statement I added this line of code, waitpid(-1,&status,WNOHANG), which will reap any child process that have been exited but doesn't wait if none of them have exited. Using WHOHANG allows you to see if there are any corpses to be collected without causing the process to stop waiting for a corpse.
