/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:52:24 by user42            #+#    #+#             */
/*   Updated: 2021/02/03 18:02:38 by user42           ###   ########.fr       */
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
		if (i >= 1 && !ft_strncmp(arg[i - 1], "echo", 5) &&
		ft_strncmp(arg[i], "-n", 3) != 0)
			return ;
		if (arg[i][0] == '"')
			arg_check(shell, arg[i], 1);
		else if (arg[i][0] == '\'')
			arg_check(shell, arg[i], 2);
		i++;
	}
}

static char	**cmd_tab(t_arg *arg)
{
	t_arg	*start;
	char	**tab;
	int		i;

	if (!arg)
		return (NULL);
	start = arg->next;
	i = 2;
	while (start && (!start->type || start->type > 5))
	{
		start = start->next;
		i++;
	}
	if (!(tab = malloc(sizeof(char *) * i)))
		return (NULL);
	start = arg->next;
	tab[0] = arg->str;
	i = 1;
	while (start && (!start->type || start->type > 5))
	{
		tab[i++] = start->str;
		start = start->next;
	}
	tab[i] = NULL;
	return (tab);
}

void		ft_exec(t_data *shell, t_arg *arg)
{
	char **cmds;

	if (!shell->cmd_switch)
		return ;
	cmds = cmd_tab(arg);
	arg_quote(shell, cmds);
	if (!ft_strlen(shell->cmd_line))
		return ;
	if (cmds[0][0] == '$')
		if (!exec_env(shell, cmds))
		{
			clean_str(cmds);
			return ;
		}
	if (!is_builtin(shell, cmds))
		shell->ret = exec_bin(shell, cmds);
	free(cmds);
	if (shell->pip_in > 0)
		close(shell->pip_in);
	if (shell->pip_out > 0)
		close(shell->pip_out);
	shell->pip_in = -1;
	shell->pip_out = -1;
	shell->cmd_switch = 0;
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
