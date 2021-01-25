/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:36:19 by user42            #+#    #+#             */
/*   Updated: 2021/01/25 12:28:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		close_fd(t_data *shell)
{
	if (shell->fd_in > 0)
		close(shell->fd_in);
	if (shell->fd_out > 0)
		close(shell->fd_out);
	if (shell->pip_in > 0)
		close(shell->pip_in);
	if (shell->pip_out > 0)
		close(shell->pip_out);
}

void		reset_fd(t_data *shell)
{
	dup2(shell->in, 0);
	dup2(shell->out, 1);
}

void		reset_stds(t_data *shell)
{
	shell->pip_in = -1;
	shell->pip_out = -1;
	shell->fd_in = -1;
	shell->fd_out = -1;
	shell->pid = -1;
}

void		close_onefd(int fd)
{
	if (fd > 0)
		close(fd);
}
