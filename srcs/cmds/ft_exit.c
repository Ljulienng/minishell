/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 15:21:34 by user42            #+#    #+#             */
/*   Updated: 2021/01/14 16:26:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_data *shell)
{
	shell->exit = 1;
	ft_printf_fd(STDERR, "exit\n");
	if (shell->arg[1] && shell->arg[2])
	{
		shell->ret = 1;
		ft_printf_fd(STDERR, "minishell: exit: too many arguments\n");
	}
	else if (shell->arg[1] && !ft_argisnum(shell->arg[1]))
	{
		shell->ret = 255;
		ft_printf_fd(STDERR, "minishell: exit: %s : \
		numeric argument required\n", shell->arg[1]);
	}
	else if (shell->arg[1])
		shell->ret = ft_atoi(shell->arg[1]);
	else
		shell->ret = 0;
}
