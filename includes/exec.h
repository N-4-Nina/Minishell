#ifndef EXEC_H
#define EXEC_H

//#include "nsh.h"

typedef struct s_simple
{
    int input;
    int output;
    char    *heredoc;
    int hasheredoc;
    int isbuiltin;
    int has_cmd_word;
    int argc;
    int filesnb;
    int *files;
    char *path;
    char **argv;   
}              t_smpl;

typedef struct s_command
{
    int     i;
    int     smpnb;
    int     *red[2];
    int     *ori[2];
    t_smpl  **smpl;
}               t_cmd;

int exec(t_sh *nsh);

//cmd
int	fork_single(t_smpl *smpl, t_env *env, int *status);
int exec_single(t_sh *nsh, t_smpl *s);
int cmd_execute(t_sh *nsh, t_cmd *cmd);
int cmd_build(t_sh *nsh, t_ast *node, t_cmd *cmd);
void    cmd_reset(t_cmd *cmd);

//files
int     open_file(t_smpl *s, char *file, char *hd, int flags);
int     get_flags(char *red);
void    close_files(t_smpl *s);

//simple
void    init_simple(t_smpl *s, int ac, int fc);
t_smpl *build_simple(t_sh *nsh, t_ast *node);

//pipe_seq
int exec_pipe_seq(t_sh *nsh, t_cmd *cmd);

int call_builtin(t_sh *nsh, t_smpl *s);
int spawn(t_smpl *smpl, t_env *env);

//word
int    id_cmd_word(t_smpl *s, t_ast *node, t_sh *nsh);
int    handle_word_suf(t_smpl *s, t_ast *node, t_env *env, int *status);
int     id_cmd_suffix(t_smpl *s, t_ast *node, t_sh *nsh);

//io
int    handle_io_suf(t_smpl *s, t_ast *node, t_env *env, int *status);
int    handle_io_first(t_smpl *s, t_ast *node, t_sh *nsh);

//path
int set_cmd_path(t_smpl *s, t_env *env, char *name);

//redirect
void    redirect(t_smpl *s, int *ori_in, int *ori_out);
void    recover_origin(int origin[2]);


#endif