/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 13:47:34 by user42            #+#    #+#             */
/*   Updated: 2021/02/03 15:07:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_semicolon(t_data *shell, int option)
{
	int		i;
	int		j;
	char	**arg;

	i = 0;
	j = 0;
	while (shell->arg[i] && ft_strncmp(shell->arg[i], ";", 2))
		i++;
	i++;
	lst_malloc((void **)&arg, sizeof(char *)\
	* (shell->arg_nb - i + 2), shell);
	while (shell->arg[i])
	{
		lst_malloc((void **)&arg[j], ft_strlen(shell->arg[i]) + 1, shell);
		ft_strcpy(arg[j++], shell->arg[i++]);
	}
	arg[j] = NULL;
	i = 0;
	if (option)
		free_arg(shell);
	shell->arg = arg;
}

void	print_env2(t_data *shell, char *str, int *i)
{
	char	tmp[1024];
	int		j;

	if (str[*i] == '$' && !str[*i + 1])
		return ;
	j = 0;
	tmp[0] = '\0';
	*i += 1;
	while (str[*i] && !is_from(str[*i], ";|<> "))
	{
		tmp[j] = str[*i];
		j++;
		*i += 1;
	}
	tmp[j] = '\0';
	print_env(shell, tmp);
}
