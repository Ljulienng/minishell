/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 14:14:01 by user42            #+#    #+#             */
/*   Updated: 2021/01/28 16:35:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_env2(t_data *shell, char *str, int *i)
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

static void	print_echo(t_data *shell, char *str, int quote)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && !is_from(str[i + 1], ";|<> ")\
			&& !shell->squote_env)
			print_env2(shell, str, &i);
		if ((!quote || quote == 2) && \
		str[i] == '\\' && is_from(str[i + 1], "\\\""))
		{
			ft_printf("%c", str[i + 1]);
			i++;
		}
		else
			ft_printf("%c", str[i]);
		i++;
	}
}

static int	clean_arg2(t_data *shell, char *str, int *back)
{
	int i;

	i = 0;
	*back = 0;
	while (str[i])
		if (str[i++] == '\\')
			*back += 1;
	if (str[0] == '"')
	{
		shell->dquote_flag = 1;
		return (2);
	}
	else if (str[0] == '\'')
	{
		shell->squote_flag = 1;
		return (1);
	}
	return (0);
}

static int	clean_arg(t_data *shell, char *str)
{
	int	i;
	int	j;
	int	ret;
	int	back;

	i = 0;
	j = 0;
	ret = clean_arg2(shell, str, &back);
	while (str[i])
	{
		if (str[i] == '$' && shell->squote_flag)
			shell->squote_env = 1;
		if (str[i] == '\'' && shell->dquote_flag)
			str[j++] = str[i];
		else if (str[i] == '"' && shell->squote_flag)
			str[j++] = str[i];
		else if (!is_from(str[i], "'\"") || (i > 1 && \
		back % 2 != 0 && str[i - 1] == '\\' && str[i] == '"'))
			str[j++] = str[i];
		i++;
		quote_switch2(shell, &i, str, back);
	}
	while (str[j] != '\0')
		str[j++] = '\0';
	return (ret);
}

int			ft_echo(t_data *shell)
{
	int	i;
	int ret;

	i = 1;
	if (shell->arg[i] && !reco_cmd(shell->arg[i], "-n"))
	{
		shell->n_flag = 1;
		i++;
	}
	while (i < shell->arg_nb && shell->arg[i] \
	&& !(is_option(shell, shell->arg[i])))
	{
		ret = clean_arg(shell, shell->arg[i]);
		print_echo(shell, shell->arg[i], ret);
		if (shell->arg[i + 1] != NULL && !is_from(shell->arg[i + 1][0], ";|<>"))
			ft_printf(" ");
		shell->squote_env = 0;
		i++;
	}
	if (!shell->n_flag)
		ft_printf("\n");
	return (0);
}
