#include "../../includes/nsh.h"

int exec_seq_part(t_sh *nsh, t_smpl *s, int red[2], int fd)
{
    printf("%s =  %d, %d \n", s->path, s->input, s->output);
    if (s->input != -1 && s->input != STDIN_FILENO)
        dup2(s->input, STDIN_FILENO);
    if (s->output != -1 && s->output != STDOUT_FILENO)
        dup2(s->output, STDOUT_FILENO);
    if (s->isbuiltin >= 0)
    {
        call_builtin(nsh, s);
    }
    else
    {
        execve(s->path, s->argv, NULL);
    }
    dup2(fd, STDIN_FILENO);
    dup2(red[1], STDOUT_FILENO);
    return (0);
}

int exec_pipe_seq(t_sh *nsh, t_cmd *cmd)
{
    int     i;
    int     red[2];
    //int     origin[2];
    int     fd;
    pid_t   pid;

    i = 0;
    red[0] = 0;
    red[1] = 1;
    fd = 0;
    while (i < cmd->smpnb)
    {
        if (pipe(red))
            write(1, "pipe creation error", 18);
        pid = fork();
        if (!pid)
        {
            dup2(fd, 0);
            if (i < cmd->smpnb - 1)
                dup2(red[1], 1);
            close(red[0]);
            //execve(cmd->smpl[i]->path, cmd->smpl[i]->argv, NULL);
            exec_seq_part(nsh, cmd->smpl[i], red, fd);
        }
        else
        {
            wait(0);
            //waitpid(0, NULL, 0);
            close(red[1]);
            fd =red[0];
        }
        i++;
    } 
    (void)nsh;
    return (0);
}