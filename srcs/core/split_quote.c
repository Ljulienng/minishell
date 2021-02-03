/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:08:16 by user42            #+#    #+#             */
/*   Updated: 2021/02/03 19:27:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			quote_switch2(t_data *shell, int *i, char *str, int back)
{
	if (*i > 1 && str[*i - 1] == '\\' && str[*i - 2] == ' '
	&& is_from(str[*i], "\"'"))
		return ;
	if ((*i >= 1 && back % 2 != 0 && str[*i - 1] == '\\') && str[*i] == '"')
		return ;
	else if ((*i >= 1 && back % 2 != 0 && \
	str[*i - 1] == '\\') && str[*i] == '\'')
		return ;
	else if ((*i > 1 && back % 2 == 0 && str[*i - 1] == '\\'
	&& str[*i - 2] != '\\') && is_from(str[*i], "\"'"))
		return ;
	if (!shell->squote_flag && str[*i] == '"')
	{
		if (shell->dquote_flag)
			shell->dquote_flag = 0;
		else
			shell->dquote_flag = 1;
	}
	if (!shell->dquote_flag && str[*i] == '\'')
	{
		if (shell->squote_flag)
			shell->squote_flag = 0;
		else
			shell->squote_flag = 1;
	}
}

void			quote_switch(t_data *shell, int *i, char *str)
{
	if ((*i >= 1 && str[*i - 2] != '\\' && \
	str[*i - 1] == '\\') && str[*i] == '"')
		return ;
	if (!shell->squote_flag && str[*i] == '"')
	{
		if (shell->dquote_flag)
			shell->dquote_flag = 0;
		else
			shell->dquote_flag = 1;
	}
	if (!shell->dquote_flag && str[*i] == '\'')
	{
		if (shell->squote_flag)
			shell->squote_flag = 0;
		else
			shell->squote_flag = 1;
	}
}

static void		handle_dquote(t_data *shell, int *i, int *y, int back)
{
	quote_switch2(shell, i, shell->cmd_line, back);
	while (shell->cmd_line[*i])
	{
		shell->arg[shell->i][*y] = shell->cmd_line[*i];
		*i += 1;
		*y += 1;
		quote_switch2(shell, i, shell->cmd_line, back);
		if (!shell->dquote_flag && !shell->squote_flag && \
			(shell->cmd_line[*i + 1] == ' ' || !shell->cmd_line[*i + 1]))
			break ;
	}
	shell->arg[shell->i][*y] = shell->cmd_line[*i];
	*i += 1;
}

void			count_options(t_data *shell)
{
	int i;

	i = 0;
	while (shell->arg[i])
	{
		if (ft_strncmp(shell->arg[i], ";", 2) == 0)
			shell->params.semicolon++;
		else if (ft_strncmp(shell->arg[i], ">", 2) == 0)
			shell->params.r_angle++;
		else if (ft_strncmp(shell->arg[i], "|", 2) == 0)
			shell->params.pipe++;
		else if (ft_strncmp(shell->arg[i], "<", 2) == 0)
			shell->params.l_angle++;
		else if (ft_strncmp(shell->arg[i], ">>", 3) == 0)
			shell->params.d_angle++;
		i++;
	}
	if (shell->params.semicolon || shell->params.r_angle \
	|| shell->params.pipe || shell->params.l_angle || shell->params.d_angle)
		shell->params.has_option = 1;
}

int				split_quote(t_data *shell, int *i, int *y)
{
	int j;
	int	back;

	back = 0;
	j = 0;
	shell->dquote_flag = 0;
	shell->squote_flag = 0;
	while (shell->cmd_line[j])
		if (shell->cmd_line[j++] == '\\')
			back++;
	if (is_from(shell->cmd_line[*i], "\"'"))
		handle_dquote(shell, i, y, back);
	if (!shell->dquote_flag && !shell->squote_flag)
		return (1);
	else
		return (error_exit(0, "One quote or double quote is missing"));
}
