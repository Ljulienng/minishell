/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 18:48:26 by julienngy         #+#    #+#             */
/*   Updated: 2021/01/26 18:39:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		full_clean(t_data *shell, int *ret)
{
	*ret = shell->ret;
	free_env(shell);
	ft_lstclear(&(shell->trash), &free);
	free(shell);
}

int			reco_cmd(char *str, char *cmd)
{
	int		ret;
	size_t	size;

	size = ft_strlen(str);
	ret = ft_strncmp(str, cmd, ft_strlen(cmd));
	if (size < ft_strlen(cmd))
		ret = -1;
	return (ret);
}

void		clean_str(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char		**reduce_arg(t_data *shell)
{
	char	**arg;
	int		i;

	i = 0;
	while (shell->arg[i] && !is_option(shell, shell->arg[i]))
		i++;
	i++;
	if (!(arg = malloc(i * sizeof(char *))))
		return (NULL);
	i = 0;
	while (shell->arg[i] && !is_option(shell, shell->arg[i]))
	{
		if (!(arg[i] = malloc(ft_strlen(shell->arg[i]) + 1)))
			return (NULL);
		ft_strcpy(arg[i], shell->arg[i]);
		i++;
	}
	arg[i] = NULL;
	return (arg);
}

int			current_arg(t_data *shell, int opt_index)
{
	int i;

	i = opt_index;
	while (i > 0)
	{
		if (is_option(shell, shell->arg[i - 1]))
			break ;
		i--;
	}
	return (i);
}
