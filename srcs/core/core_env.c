/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:48:42 by user42            #+#    #+#             */
/*   Updated: 2021/01/28 16:33:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		add_env(t_data *shell, char *env)
{
	int		i;
	char	**tmp_env;

	i = 0;
	while (shell->env[i])
		i++;
	lst_malloc((void **)&tmp_env, sizeof(char *) * (i + 2), shell);
	i = 0;
	while (shell->env[i])
	{
		if (!(tmp_env[i] = ft_strdup(shell->env[i])))
			return (0);
		i++;
	}
	if (!(tmp_env[i++] = ft_strdup(env)))
		return (0);
	tmp_env[i] = NULL;
	free_env(shell);
	shell->env = tmp_env;
	return (1);
}

void	init_env(t_data *shell, char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	lst_malloc((void **)&shell->env, sizeof(char *) * (i + 1), shell);
	i = 0;
	while (env[i])
	{
		if (!(shell->env[i] = ft_strdup(env[i])))
			return ;
		i++;
	}
	shell->env[i] = NULL;
}

void	free_env(t_data *shell)
{
	int i;

	i = 0;
	while (shell->env[i])
	{
		free(shell->env[i]);
		i++;
	}
}

void	print_env(t_data *shell, char *env)
{
	int i;

	i = 0;
	if (ft_strncmp(env, "?", 2) == 0)
		ft_printf("%d", shell->ret);
	while (shell->env[i])
	{
		if (!(ft_strncmp(env, shell->env[i], ft_strlen(env))))
		{
			ft_printf("%s", shell->env[i] + ft_strlen(env) + 1);
			return ;
		}
		i++;
	}
}

int		exec_env(t_data *shell, char **arg)
{
	int		i;
	int		ret;
	char	*tmp;

	ret = 0;
	i = 0;
	while (shell->env[i])
	{
		if (!(ft_strncmp(arg[0] + 1, shell->env[i]\
		, ft_strlen(arg[0]) - 1)))
		{
			ret = 1;
			break ;
		}
		i++;
	}
	if (ret)
	{
		if (!(tmp = malloc(ft_strlen(shell->env[i] + 1))))
			return (0);
		ft_strcpy(tmp, shell->env[i] + ft_strlen(arg[0]));
		free(arg[0]);
		arg[0] = tmp;
	}
	return (ret);
}
