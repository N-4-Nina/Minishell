/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:27:36 by chpl              #+#    #+#             */
/*   Updated: 2021/09/14 09:57:51 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

int		exec(t_sh *nsh);
int		build_exec(t_sh *nsh, t_ast *node);
//cmd
int		fork_single(t_smpl *smpl, t_env *env, int *status);
int		exec_single(t_sh *nsh, t_smpl *s);
int		cmd_execute(t_sh *nsh, t_cmd *cmd);
int		cmd_build(t_sh *nsh, t_ast *node, t_cmd *cmd);
void	cmd_reset(t_cmd *cmd);

//files
int		open_file(t_smpl *s, char *file, char *hd, int flags);
int		get_flags(char *red);
void	close_files(t_smpl *s);
int		here_doc(t_smpl *s, char *hd, char *end);
char	*update_heredoc_name(char *hd);

//simple
void	init_simple(t_smpl *s, int fc);
t_smpl	*build_simple(t_sh *nsh, t_ast *node);

//pipe_seq
int		exec_pipe_seq(t_sh *nsh, t_cmd *cmd);
int		call_builtin(t_sh *nsh, t_smpl *s);
int		spawn(t_smpl *smpl, t_env *env);
void	await_child(int *status);
int     await_children(t_sh *nsh, t_cmd *cmd);

//word
int		id_cmd_word(t_smpl *s, t_ast *node, t_sh *nsh);
int		handle_word_suf(t_smpl *s, t_ast *node, t_env *env, int *status);
int		id_cmd_suffix(t_smpl *s, t_ast *node, t_sh *nsh);

//io
int		handle_io_suf(t_smpl *s, t_ast *node, t_env *env, int *status);
int		handle_io_first(t_smpl *s, t_ast *node, t_sh *nsh);

//path
int		set_cmd_path(t_smpl *s, t_env *env, char *name);

//redirect
void	redirect(t_smpl *s, int *ori_in, int *ori_out);
void	recover_origin(int origin[2]);

//expansion
int		do_cat(char **dst, char *src);
int		replace_backslash(char **dst, char *src);
int		replace_weak(char **dst, char *src, t_env *env, int *status);
int		replace_strong(char **dst, char *src);
int		replace_var(char **dst, char *src, t_env *env, t_smpl *smpl);
int		replace_status(char **dst, char *src, int status);
char	*expand_word(char *s, t_env *env, int *status, t_smpl *smpl);
char	*expand_io(char *s, t_env *env, int *status, t_smpl *smpl);

#endif