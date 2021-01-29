/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:02:13 by user42            #+#    #+#             */
/*   Updated: 2021/01/28 16:07:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		prev_option(t_data *shell, int index)
{
	int i;

	if (index == 0)
		return (NONE);
	i = index;
	while (i > 0)
	{
		if (ft_strncmp(shell->arg[i], ";", 2) == 0)
			return (SEMI_C);
		else if (ft_strncmp(shell->arg[i], "|", 2) == 0)
			return (PIPE);
		else if (ft_strncmp(shell->arg[i], ">", 2) == 0)
			return (R_ANGLE);
		else if (ft_strncmp(shell->arg[i], "<", 2) == 0)
			return (L_ANGLE);
		else if (ft_strncmp(shell->arg[i], ">>", 3) == 0)
			return (D_ANGLE);
		i--;
	}
	return (NONE);
}

int		curr_option(t_data *shell, int option)
{
	int i;

	i = option;
	while (shell->arg[i])
	{
		if (ft_strncmp(shell->arg[i], ";", 2) == 0)
			return (SEMI_C);
		else if (ft_strncmp(shell->arg[i], "|", 2) == 0)
			return (PIPE);
		else if (ft_strncmp(shell->arg[i], ">", 2) == 0)
			return (R_ANGLE);
		else if (ft_strncmp(shell->arg[i], "<", 2) == 0)
			return (L_ANGLE);
		else if (ft_strncmp(shell->arg[i], ">>", 3) == 0)
			return (D_ANGLE);
		i++;
		shell->params.arg_index = i;
	}
	return (NONE);
}

int		next_option(t_data *shell, int i)
{
	int j;

	j = i;
	while (shell->arg[j] != NULL)
	{
		if (ft_strncmp(shell->arg[j], ";", 2) == 0)
			return (SEMI_C);
		else if (ft_strncmp(shell->arg[j], "|", 2) == 0)
			return (PIPE);
		else if (ft_strncmp(shell->arg[j], ">", 2) == 0)
			return (R_ANGLE);
		else if (ft_strncmp(shell->arg[j], "<", 2) == 0)
			return (L_ANGLE);
		else if (ft_strncmp(shell->arg[j], ">>", 3) == 0)
			return (D_ANGLE);
		j++;
	}
	return (NONE);
}

void	input(t_data *shell)
{
	if (shell->fd_in > 0)
		close(shell->fd_in);
	shell->fd_in = open(shell->arg[shell->params.old_index + 1]\
	, O_RDONLY, S_IRWXU);
	if (shell->fd_in == -1)
	{
		ft_printf_fd(2, "minishell >> %s : No such file or directory\n ", \
		shell->arg[shell->params.old_index + 1]);
		shell->ret = 1;
		shell->noexec = 1;
		return ;
	}
	dup2(shell->fd_in, 0);
}

void	redirect(t_data *shell, int curr_opt)
{
	if (shell->fd_out > 0)
		close(shell->fd_out);
	if (curr_opt == R_ANGLE)
		shell->fd_out = open(shell->arg[shell->params.old_index + 1],\
		O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else if (curr_opt == D_ANGLE)
		shell->fd_out = open(shell->arg[shell->params.old_index + 1],\
		O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (shell->fd_out == -1)
	{
		ft_printf_fd(2, "minishell >> %s : No such file or directory\n ", \
		shell->arg[shell->params.old_index + 1]);
		shell->ret = 1;
		shell->noexec = 1;
		return ;
	}
	if (curr_opt == R_ANGLE)
		shell->params.r_angle--;
	else
		shell->params.d_angle--;
	dup2(shell->fd_out, 1);
}
