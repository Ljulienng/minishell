/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 16:55:31 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 15:14:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_pwd(t_data *shell)
{
	char	*chdir;

	if (shell->arg[1] && !is_from(shell->arg[1][0], ";|<>"))
	{
		ft_printf_fd(2, "pwd: too many arguments\n");
		return (1);
	}
	chdir = NULL;
	chdir = getcwd(NULL, 0);
	ft_printf_fd(1, "%s\n", chdir);
	free(chdir);
	return (0);
}
