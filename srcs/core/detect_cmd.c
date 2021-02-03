/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 16:55:24 by user42            #+#    #+#             */
/*   Updated: 2021/02/02 17:45:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			redir_cmd(t_data *shell, t_arg *arg)
{
	t_arg	*next_opt;
	t_arg	*prev_opt;
	int		pipe;

	pipe = 0;
	prev_opt = prev_sep(arg);
	next_opt = next_sep(arg);
	if (prev_opt && (prev_opt->type == R_ANGLE || prev_opt->type == D_ANGLE))
		redirect(shell, arg);
	else if (prev_opt && prev_opt->type == L_ANGLE)
		input(shell, arg);
	else if (prev_opt && prev_opt->type == PIPE)
		pipe = ft_pipe(shell);
	if (next_opt && next_opt->type != SEMI_C && pipe != 1)
		redir_cmd(shell, next_opt->next);
	if (((prev_opt && prev_opt->type == SEMI_C) ||
	(prev_opt && prev_opt->type == PIPE)
	|| !prev_opt) && pipe != 1 && !shell->noexec)
		ft_exec(shell, arg);
}

static int		process_cmd(t_data *shell)
{
	char	*tmp;
	int		i;
	int		y;

	y = 0;
	i = 0;
	lst_malloc((void **)&tmp, ft_strlen(shell->cmd_line) + 2, shell);
	while (shell->cmd_line[i] && shell->cmd_line[i] == ' ')
		i++;
	while (shell->cmd_line[i])
	{
		while (shell->cmd_line[i] != ' ' && shell->cmd_line[i])
			tmp[y++] = shell->cmd_line[i++];
		if (shell->cmd_line[i] == ' ')
			tmp[y++] = ' ';
		i++;
	}
	tmp[y] = '\0';
	free(shell->cmd_line);
	shell->cmd_line = tmp;
	count_arg(shell);
	if (!store_arg(shell))
		return (0);
	count_options(shell);
	return (1);
}

static void		cmd_loop(t_data *shell, t_arg *current)
{
	while (!shell->exit && current)
	{
		shell->params.parent = 0;
		shell->params.child = 0;
		shell->cmd_switch = 1;
		redir_cmd(shell, current);
		reset_fd(shell);
		close_fd(shell);
		reset_stds(shell);
		current = next_run(current, 1);
		if (shell->params.child == 1)
			break ;
		shell->noexec = 0;
	}
}

void			detect_cmd(t_data *shell)
{
	int		i;
	t_arg	*current;

	i = 0;
	if (!process_cmd(shell))
		return ;
	while (shell->arg[i])
	{
		if (ft_strlen(shell->arg[i]) == 0)
			shell->arg[i] = NULL;
		i++;
	}
	if (shell->arg[0] == NULL)
		return ;
	set_arglist(shell);
	current = shell->arg_list;
	cmd_loop(shell, current);
	arg_listclear(shell->arg_list);
}
