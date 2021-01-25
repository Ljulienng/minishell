/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 09:18:28 by user42            #+#    #+#             */
/*   Updated: 2021/01/21 16:10:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_option(t_data *shell, int *i, int *y)
{
	if (is_from(shell->cmd_line[*i], ";|<>") && \
		is_from(shell->cmd_line[*i + 1], ">"))
	{
		shell->arg[shell->i][*y] = shell->cmd_line[*i];
		*i += 1;
		*y += 1;
		shell->arg[shell->i][*y] = shell->cmd_line[*i];
		*i += 1;
		*y += 1;
	}
	else if (is_from(shell->cmd_line[*i], ";|<>") && \
		!is_from(shell->cmd_line[*i + 1], ";|<>"))
	{
		shell->arg[shell->i][*y] = shell->cmd_line[*i];
		*i += 1;
		*y += 1;
	}
}

int			split_option(t_data *shell, int *i, int *y)
{
	if (is_from(shell->cmd_line[*i], ";|<>"))
		handle_option(shell, i, y);
	else
		return (error_exit(0, "One quote or double quote is missing"));
	return (1);
}
