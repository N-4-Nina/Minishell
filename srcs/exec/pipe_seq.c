#include "../../includes/nsh.h"

pid_t    spawn_seq(t_sh *nsh, int pipe[2], t_smpl *smpl)
{
    pid_t   pid;

    pid = fork();
    if (pid == -1)
    {
        //set status
        nsh_exit(nsh, NULL);
    }
    if (pid)
        return (pid);
    else
    {
        dup2(STDOUT_FILENO, pipe[1]);
        dup2(STDIN_FILENO, pipe[0]);
        if (execve(smpl->path, smpl->argv, NULL) == -1)
			printf("couldn't exec%s\n", smpl->path);
        return (0);
    }
}

pid_t    spawn_first(t_sh *nsh, int pipe[2], t_smpl *smpl)
{
    pid_t   pid;

    pid = fork();
    if (pid == -1)
    {
        //set status
        nsh_exit(nsh, NULL);
    }
    if (pid)
        return (pid);
    else
    {
        close(pipe[0]);
        dup2(STDOUT_FILENO, pipe[1]);
        if (execve(smpl->path, smpl->argv, NULL) == -1)
			printf("couldn't exec%s\n", smpl->path);
        return (0);
    }
}

pid_t    spawn_last(t_sh *nsh, int pipe[2], t_smpl *smpl)
{
    pid_t   pid;

    pid = fork();
    if (pid == -1)
    {
        //set status
        nsh_exit(nsh, NULL);
    }
    if (pid)
        return (pid);
    else
    {
        close(pipe[1]);
        dup2(STDIN_FILENO, pipe[0]);
        if (execve(smpl->path, smpl->argv, NULL) == -1)
			printf("couldn't exec %s\n", smpl->path);
        return (0);
    }
}

int exec_pipe_seq(t_sh *nsh, t_cmd *cmd)
{
    int     i;
    int     red[2];
    //int     origin[2];
    int     fd;
    t_pid   pid;

    i = cmd->smpnb - 1;
    red[0] = 0;
    red[1] = 1;
    fd = 0;
    while (i >= 0)
    {
        if (pipe(red))
            write(1, "pipe creation error", 18);
        pid = fork();
        if (!pid)
        {
            dup2()
        }
        else
        {

        }
        i++;
    }
    waitpid(0);
    (void)nsh;
    return (0);
}