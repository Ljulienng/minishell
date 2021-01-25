/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 14:14:01 by user42            #+#    #+#             */
/*   Updated: 2021/01/22 15:10:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_env2(t_data *shell, char *str, int *i)
{
	char	tmp[1024];
	int		j;

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

static void	print_echo(t_data *shell, char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && !is_from(str[i + 1], ";|<> ")\
			&& !shell->squote_env)
			print_env2(shell, str, &i);
		ft_printf("%c", str[i]);
		i++;
	}
}

static void	clean_arg(t_data *shell, char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		quote_switch(shell, &i, str);
		if (str[i] == '$' && shell->squote_flag)
			shell->squote_env = 1;
		if (str[i] == '\'' && shell->dquote_flag)
			str[j++] = str[i];
		else if (str[i] == '"' && shell->squote_flag)
			str[j++] = str[i];
		else if (!is_from(str[i], "'\""))
			str[j++] = str[i];
		i++;
	}
	while (str[j] != '\0')
		str[j++] = '\0';
}

int			ft_echo(t_data *shell)
{
	int	i;

	i = 1;
	if (shell->arg[i] && !reco_cmd(shell->arg[i], "-n"))
	{
		shell->n_flag = 1;
		i++;
	}
	while (i < shell->arg_nb && shell->arg[i] \
	&& !(is_option(shell, shell->arg[i])))
	{
		clean_arg(shell, shell->arg[i]);
		print_echo(shell, shell->arg[i]);
		if (shell->arg[i + 1] != NULL && !is_from(shell->arg[i + 1][0], ";|<>"))
			ft_printf(" ");
		shell->squote_env = 0;
		i++;
	}
	if (!shell->n_flag)
		ft_printf("\n");
	return (0);
}
