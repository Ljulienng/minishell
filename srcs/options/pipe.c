/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:52:24 by user42            #+#    #+#             */
/*   Updated: 2021/01/28 16:22:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	arg_check(t_data *shell, char *arg, int quote_type)
{
	int i;
	int j;

	i = 0;
	j = 1;
	while (j < (int)ft_strlen(arg) - 1)
		arg[i++] = arg[j++];
	arg[i] = '\0';
	if (quote_type == 1 && is_from(arg[0], "\""))
		arg_check(shell, arg, 1);
	else if (quote_type == 2 && is_from(arg[0], "'"))
		arg_check(shell, arg, 2);
}

static void	arg_quote(t_data *shell, char **arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (arg[i][0] == '"')
			arg_check(shell, arg[i], 1);
		else if (arg[i][0] == '\'')
			arg_check(shell, arg[i], 2);
		i++;
	}
}

static char	**arg_pipe(t_data *shell, int index)
{
	char	**arg;
	int		i;
	int		j;

	i = index;
	j = 0;
	while (shell->arg[i] && !is_option(shell, shell->arg[i]))
	{
		j++;
		i++;
	}
	if (!(arg = malloc((j + 1) * sizeof(char *))))
		return (NULL);
	i = index;
	j = 0;
	while (shell->arg[i] && !is_option(shell, shell->arg[i]))
	{
		if (!(arg[j] = malloc(ft_strlen(shell->arg[i]) + 1)))
			return (NULL);
		ft_strcpy(arg[j++], shell->arg[i++]);
	}
	arg[j] = NULL;
	return (arg);
}

void		start_piping(t_data *shell, int index)
{
	char **arg;

	arg = arg_pipe(shell, index);
	arg_quote(shell, arg);
	if (!ft_strlen(shell->cmd_line))
		return ;
	if (shell->arg[0][0] == '$')
		if (!exec_env(shell, arg))
		{
			clean_str(arg);
			return ;
		}
	if (!is_builtin(shell, arg))
		shell->ret = exec_bin(shell, arg);
	if (arg[0] && arg)
		clean_str(arg);
	if (shell->pip_in > 0)
		close(shell->pip_in);
	if (shell->pip_out > 0)
		close(shell->pip_out);
	shell->pip_in = -1;
	shell->pip_out = -1;
}

int			ft_pipe(t_data *shell)
{
	int		pipe_fd[2];
	pid_t	pid;

	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		close_onefd(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		shell->pip_in = pipe_fd[0];
		shell->pid = -1;
		shell->params.child = 1;
		shell->noexec = 0;
		return (2);
	}
	else
	{
		close_onefd(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		shell->pip_out = pipe_fd[1];
		shell->pid = pid;
		shell->params.parent = 1;
		return (1);
	}
}
