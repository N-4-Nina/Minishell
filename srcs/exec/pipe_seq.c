#include "../../includes/nsh.h"

void    do_fork(t_sh *nsh, pid_t *pid)
{
    *pid = fork();
    if (*pid == -1)
    {
        //set status
        nsh_exit(nsh, void);
    }
}

int exec_pipe_seq(t_sh *nsh, t_cmd *cmd)
{
    int     i;
    int     red[2];
    int     origin[2];

    i = 0;
    origin[0] = 0;
    origin[1] = 1;

    while (i < cmd->smpnb)
    {

        i++;
    }
    (void)nsh;
    (void)cmd;
    return (0);
}