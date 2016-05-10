#include "lab4.h"

/* Shell input line */
int process(void)
{
    char *arg[MAXARG + 1];  /* pointer array for runcommand */
    int toktype;            /* type of token in command */
    int narg ;              /* number of arguments so far */
    int type;               /* type = FOREGROUND or BACKGROUND */

    while (1) 
    {
        /* Take action according to token type */
        switch(toktype = gettok(&arg[narg]))
        {
            case ARG:
                if(narg < MAXARG) 
                {
                    narg++;
                }
                break;

            case EOL:
            
            case SEMICOLON:
            
            case AMPERSAND:
                type = toktype == AMPERSAND ? BACKGROUND : FOREGROUND;
                
                if(narg != 0)
                {
                    arg[narg] = 0;
                    runcommand(arg,type);
                }

                if(toktype == EOL)
                {
                    return;   
                }

                narg = 0;
                
                break;
        }
    }
}