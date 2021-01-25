/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 16:55:24 by user42            #+#    #+#             */
/*   Updated: 2021/01/22 19:40:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			redir_cmd2(t_data *shell, int pipe, int next_opt, int prev_opt)
{
	if (shell->pid > 0 && !pipe && !shell->noexec)
		start_piping(shell, current_arg(shell, shell->params.old_index));
	else if ((prev_opt == PIPE || !prev_opt || prev_opt == SEMI_C) \
	&& pipe == 2 && !shell->noexec && next_opt > 1)
		start_piping(shell, current_arg(shell, shell->params.old_index));
	else if ((prev_opt == PIPE || !prev_opt || prev_opt == SEMI_C) \
	&& pipe == 2 && !shell->noexec && next_opt < 2)
		start_piping(shell, current_arg(shell, shell->params.arg_index));
	else if ((prev_opt == PIPE || !prev_opt) && pipe == 0 && !shell->noexec\
	&& (!shell->params.child && !shell->params.parent))
		start_piping(shell, current_arg(shell, shell->params.old_index));
	else if ((prev_opt == PIPE || !prev_opt) && pipe == 0 && !shell->noexec\
	&& (shell->params.child && !shell->params.parent) &&\
	!shell->params.semicolon && next_opt < 2)
		start_piping(shell, current_arg(shell, shell->params.old_index));
}

void			redir_cmd(t_data *shell, int index)
{
	int next_opt;
	int prev_opt;
	int pipe;

	shell->params.old_index = shell->params.arg_index;
	pipe = 0;
	prev_opt = prev_option(shell, index);
	next_opt = curr_option(shell, index);
	if (shell->pid == -1 && (prev_opt == R_ANGLE || prev_opt == D_ANGLE))
		redirect(shell, prev_opt);
	else if (prev_opt == L_ANGLE)
		input(shell);
	else if (prev_opt == PIPE)
		pipe = ft_pipe(shell);
	if (next_opt && next_opt != SEMI_C && pipe != 1)
		redir_cmd(shell, shell->params.arg_index + 1);
	redir_cmd2(shell, pipe, next_opt, prev_opt);
}

static int		process_cmd(t_data *shell)
{
	char	*tmp;
	int		i;
	int		y;

	y = 0;
	i = 0;
	lst_malloc((void **)&tmp, ft_strlen(shell->cmd_line) + 2, shell);
	while (shell->cmd_line[i] == ' ')
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

void			detect_cmd(t_data *shell)
{
	int i;

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
	redir_cmd(shell, 0);
	if (((shell->params.child && !shell->params.parent) \
	|| (!shell->params.child \
	&& !shell->params.parent)) && shell->params.semicolon && shell->pid == -1)
		do_next_cmd(shell);
}
