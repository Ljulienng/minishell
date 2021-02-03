/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:02:13 by user42            #+#    #+#             */
/*   Updated: 2021/02/02 16:06:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_arg	*next_sep(t_arg *arg)
{
	while (arg && (!arg->type || arg->type > 5))
		arg = arg->next;
	return (arg);
}

t_arg	*prev_sep(t_arg *arg)
{
	while (arg && (!arg->type || arg->type > 5))
		arg = arg->prev;
	return (arg);
}

void	input(t_data *shell, t_arg *arg)
{
	if (shell->fd_in > 0)
		close(shell->fd_in);
	shell->fd_in = open(arg->str, O_RDONLY, S_IRWXU);
	if (shell->fd_in == -1)
	{
		ft_printf_fd(2, "minishell >> %s : No such file or directory\n ", \
		arg->str);
		shell->ret = 1;
		shell->noexec = 1;
		return ;
	}
	dup2(shell->fd_in, 0);
}

void	redirect(t_data *shell, t_arg *arg)
{
	if (shell->fd_out > 0)
		close(shell->fd_out);
	if (arg->prev->type == R_ANGLE)
		shell->fd_out = open(arg->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else if (arg->prev->type == D_ANGLE)
		shell->fd_out = open(arg->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (shell->fd_out == -1)
	{
		ft_printf_fd(2, "minishell >> %s : No such file or directory\n ", \
		arg->str);
		shell->ret = 1;
		shell->noexec = 1;
		return ;
	}
	if (arg->type == R_ANGLE)
		shell->params.r_angle--;
	else
		shell->params.d_angle--;
	dup2(shell->fd_out, 1);
}
