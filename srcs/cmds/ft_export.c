/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 15:52:46 by user42            #+#    #+#             */
/*   Updated: 2021/01/14 16:26:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (shell->arg[*i][0] == '=')
	{
		shell->error = 1;
		return (0);
	}
	while (shell->arg[*i][*j] != '=')
	{
		buff[*j] = shell->arg[*i][*j];
		*j += 1;
	}
	buff[*j] = '\0';
	*j += 1;
	return (1);
}

void		ft_export(t_data *shell)
{
	char	buff[256];
	int		i;
	int		j;

	i = 1;
	while (shell->arg[i])
	{
		j = 0;
		if (is_from('=', shell->arg[i]))
		{
			if (!(ft_export2(shell, &i, &j, buff)))
				break ;
			if (checkin_env(shell, buff))
				del_env(shell, buff);
			add_env(shell, shell->arg[i]);
		}
		i++;
	}
}
