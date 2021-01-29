/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:44:38 by user42            #+#    #+#             */
/*   Updated: 2021/01/28 15:45:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		str_env_len(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static void		sort_env(char **tab, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = 0;
	while (tab && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}

void			sorted_env(t_data *shell)
{
	int		i;

	sort_env(shell->env, str_env_len(shell->env));
	i = 0;
	while (shell->env[i])
	{
		ft_printf("declare -x %s\n", shell->env[i]);
		i++;
	}
}

int				is_valid_env(char *env)
{
	int		i;

	i = 0;
	if (ft_isdigit(env[i]) == 1)
		return (0);
	while (env[i] && env[i] != '=')
	{
		if (ft_isalnum(env[i]) == 0)
			return (-1);
		i++;
	}
	if (env[i] != '=')
		return (2);
	return (1);
}
