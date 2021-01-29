/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 15:52:46 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 14:51:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	print_error(int error, char *arg)
{
	int		i;

	if (error == -1)
		ft_printf_fd(2, "export: not valid in this context: ");
	else if (error == 0 || error == -3)
		ft_printf_fd(2, "export: not a valid identifier: ");
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write(2, &arg[i], 1);
		i++;
	}
	write(2, "\n", 1);
	return (1);
}

static int	checkin_env(t_data *shell, char *env)
{
	int i;

	i = 0;
	while (shell->env[i])
	{
		if (!(ft_strncmp(shell->env[i], env, ft_strlen(env))))
			return (1);
		i++;
	}
	return (0);
}

static int	ft_export2(t_data *shell, int *i, int *j, char *buff)
{
	int ret;

	ret = 1;
	if (shell->arg[*i][0] == '=')
		ret = -3;
	ret = is_valid_env(shell->arg[*i]);
	if (ret <= 0)
		return (print_error(ret, shell->arg[*i]));
	while (shell->arg[*i][*j] != '=')
	{
		buff[*j] = shell->arg[*i][*j];
		*j += 1;
	}
	buff[*j] = '\0';
	*j += 1;
	return (0);
}

int			ft_export(t_data *shell)
{
	char	buff[256];
	int		i;
	int		j;

	i = 1;
	if (!shell->arg[i])
	{
		sorted_env(shell);
		shell->ret = 0;
		return (0);
	}
	while (shell->arg[i])
	{
		j = 0;
		if (is_from('=', shell->arg[i]))
		{
			if (ft_export2(shell, &i, &j, buff))
				return (1);
			if (checkin_env(shell, buff))
				del_env(shell, buff);
			add_env(shell, shell->arg[i]);
		}
		i++;
	}
	return (0);
}
