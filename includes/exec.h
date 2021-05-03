#ifndef EXEC_H
#define EXEC_H

//#include "nsh.h"

typedef struct s_simple
{
    int input;
    int output;
    int isbuiltin;
    int argc;
    int filesnb;
    int *files;
    char *name;
    char *path;
    char **argv;
    struct s_simple *next;    
}              t_smpl;

typedef struct s_command
{
    int smpnb;
    t_smpl  **smpl;
}               t_cmd;

int exec(t_sh *nsh);


#endif