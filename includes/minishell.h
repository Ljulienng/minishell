/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 16:12:55 by user42            #+#    #+#             */
/*   Updated: 2021/01/28 20:16:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <signal.h>
# include "../libft/includes/libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define NONE 0
# define SEMI_C 1
# define R_ANGLE 2
# define D_ANGLE 3
# define L_ANGLE 4
# define PIPE 5
# define ARG 6

typedef	struct		s_sig
{
	pid_t			pid;
	int				sig_quit;
	int				sig_int;
	int				sig_exit;

}					t_sig;

typedef struct		s_param
{
	int				has_option;
	int				r_angle;
	int				l_angle;
	int				d_angle;
	int				pipe;
	int				child;
	int				parent;
	int				semicolon;
	int				opt_index;
	int				old_index;
	int				arg_index;
	int				old_arg;
	int				switch_pipe;
}					t_param;

typedef struct		s_data
{
	char			*cmd_line;
	char			**arg;
	char			**cmd;
	char			**env;
	int				noexec;
	int				pid;
	int				is_env;
	int				pip_in;
	int				pip_out;
	int				fd_in;
	int				fd_out;
	int				in;
	int				out;
	int				squote_env;
	int				dquote_flag;
	int				squote_flag;
	int				n_flag;
	int				i;
	int				arg_nb;
	int				quotes;
	int				dquotes;
	int				error;
	int				exit;
	int				ret;
	int				oldpwd;
	int				redir;
	t_sig			*sig;
	t_param			params;
	t_list			*trash;
}					t_data;
/*
** Commands
*/
void				full_clean(t_data *shell, int *ret);
int					ft_pwd(t_data *shell);
void				ft_exit(t_data *shell);
int					ft_echo(t_data *shell);
int					ft_cd(t_data *shell);
void				ft_env(t_data *shell);
int					ft_export(t_data *shell);
void				ft_unset(t_data *shell);
int					exec_bin(t_data *shell, char **arg);
/*
** detect_cmd.c
*/
void				redir_cmd(t_data *shell, int index, int prev, int next);
void				detect_cmd(t_data *shell);
void				count_arg(t_data *shell);
int					store_arg(t_data *shell);
int					split_quote(t_data *shell, int *i, int *y);
int					split_option(t_data *shell, int *i, int *y);
void				quote_switch(t_data *shell, int *i, char *str);
void				quote_switch2(t_data *shell, int *i, char *str, int back);
void				count_options(t_data *shell);
/*
** core_env.c
*/
int					add_env(t_data *shell, char *env);
void				init_env(t_data *shell, char **env);
void				free_env(t_data *shell);
void				print_env(t_data *shell, char *env);
int					exec_env(t_data *shell, char **arg);
int					del_env(t_data *shell, char *env);
void				sorted_env(t_data *shell);
int					is_valid_env(char *env);
/*
** ft_tools.c
*/
int					reco_cmd(char *str, char *cmd);
void				reset_shell(t_data *shell);
int					error_exit(int error, char *error_msg);
int					is_from(char c, char *chars);
void				lst_malloc(void **to_malloc, size_t size, t_data *shell);
int					ft_argisnum(char *str);
void				reset_options(t_data *shell);
int					is_option(t_data *shell, char *arg);
int					is_builtin(t_data *shell, char **arg);
void				free_arg(t_data *shell);
char				*join_path(const char *s1, const char *s2);
void				clean_str(char **str);
char				**reduce_arg(t_data *shell);
/*
** signal.c
*/
void				signal_reset(t_data *shell);
void				signal_int(int code);
void				signal_quit(int code);
/*
** options
*/
void				do_next_cmd(t_data *shell);
void				close_fd(t_data *shell);
void				reset_fd(t_data *shell);
void				close_onefd(int fd);
void				reset_stds(t_data *shell);
void				redirect(t_data *shell, int curr_opt);
int					ft_pipe(t_data *shell);
void				input(t_data *shell);
int					prev_option(t_data *shell, int index);
int					curr_option(t_data *shell, int option);
int					next_option(t_data *shell, int i);
void				process_semicolon(t_data *shell, int option);
int					current_arg(t_data *shell, int opt_index);
void				start_piping(t_data *shell, int index);

extern t_sig g_sig;
#endif
