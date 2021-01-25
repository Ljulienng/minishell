/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:19:45 by user42            #+#    #+#             */
/*   Updated: 2021/01/14 16:31:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		del_env(t_data *shell, char *env)
{
	int		i;
	int		j;
	char	**tmp_env;

	i = 0;
	j = 0;
	while (shell->env[i])
		i++;
	lst_malloc((void **)&tmp_env, sizeof(char *) * (i + 1), shell);
	i = 0;
	while (shell->env[i])
	{
		if (!(ft_strncmp(shell->env[i], env, \
		ft_strlen(env))) && shell->env[i + 1])
			i++;
		else if (!(ft_strncmp(shell->env[i], env, ft_strlen(env))))
			break ;
		if (!(tmp_env[j++] = ft_strdup(shell->env[i])))
			return (0);
		i++;
	}
	tmp_env[j] = NULL;
	free_env(shell);
	shell->env = tmp_env;
	return (1);
}

void	ft_unset(t_data *shell)
{
	int i;

	i = 1;
	if (!shell->arg[i])
		ft_printf_fd(2, "unset: not enough arguments");
	while (shell->arg[i])
		del_env(shell, shell->arg[i++]);
}
