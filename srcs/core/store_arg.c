/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:13:05 by user42            #+#    #+#             */
/*   Updated: 2021/02/03 18:33:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	count_arg3(t_data *shell, int *i)
{
	if (is_from(shell->cmd_line[*i], ";|><") &&
	!shell->dquote_flag && !shell->squote_flag)
	{
		if (shell->cmd_line[*i + 1] != '>')
		{
			shell->arg_nb++;
			*i += 1;
		}
		else if (shell->cmd_line[*i + 1] == '>')
		{
			shell->arg_nb++;
			*i += 2;
		}
	}
}

static void	count_arg2(t_data *shell, int *i)
{
	if (is_from(shell->cmd_line[*i], "\"'"))
	{
		shell->arg_nb++;
		if (shell->cmd_line[*i] == '"')
			shell->dquote_flag = 1;
		else if (shell->cmd_line[*i] == '\'')
			shell->squote_flag = 1;
		while (shell->cmd_line[*i])
		{
			*i += 1;
			quote_switch(shell, i, shell->cmd_line);
			if (!shell->dquote_flag && !shell->squote_flag \
			&& shell->cmd_line[*i + 1] == ' ')
				break ;
		}
		*i += 1;
	}
}

void		count_arg(t_data *shell)
{
	int i;

	i = 0;
	shell->arg_nb = 0;
	while (shell->cmd_line[i])
	{
		count_arg2(shell, &i);
		count_arg3(shell, &i);
		if (shell->cmd_line[i] && !is_from(shell->cmd_line[i], " ;|><"))
		{
			shell->arg_nb++;
			while (shell->cmd_line[i] && !is_from(shell->cmd_line[i], " ;|><"))
				i++;
		}
		if (shell->cmd_line[i] == ' ')
			i++;
	}
}

static int	store_word(t_data *shell, int *i)
{
	int y;

	y = 0;
	lst_malloc((void **)&shell->arg[shell->i], 1024, shell);
	if (is_from(shell->cmd_line[*i], "\"'"))
		if (!split_quote(shell, i, &y))
			return (0);
	if (is_from(shell->cmd_line[*i], "<>;|"))
		if (split_option(shell, i, &y))
			return (1);
	if (!is_from(shell->cmd_line[*i], "\"'<>;| ") && shell->cmd_line[*i])
	{
		while (shell->cmd_line[*i] && !is_from(shell->cmd_line[*i], "\"'<>;| "))
		{
			shell->arg[shell->i][y++] = shell->cmd_line[*i];
			*i += 1;
			if (is_from(shell->cmd_line[*i], "\"'"))
				if (!split_quote(shell, i, &y))
					return (0);
		}
	}
	return (1);
}

int			store_arg(t_data *shell)
{
	int i;

	i = 0;
	shell->i = 0;
	lst_malloc((void **)&shell->arg, (shell->arg_nb + 2)\
	* sizeof(char *), shell);
	while (shell->cmd_line[i])
	{
		while (shell->cmd_line[i] == ' ')
			i++;
		if (!store_word(shell, &i))
			return (0);
		shell->i++;
	}
	shell->arg[shell->i] = NULL;
	shell->i = 0;
	return (1);
}
