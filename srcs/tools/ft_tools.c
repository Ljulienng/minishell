/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 15:08:24 by user42            #+#    #+#             */
/*   Updated: 2021/02/02 14:24:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reset_shell(t_data *shell)
{
	shell->noexec = 0;
	shell->redir = 0;
	shell->params.switch_pipe = 0;
	shell->n_flag = 0;
	shell->dquote_flag = 0;
	shell->squote_flag = 0;
	shell->i = 0;
	shell->pid = 0;
	shell->error = 0;
	shell->arg_nb = 0;
	shell->quotes = 0;
	shell->dquotes = 0;
	shell->cmd_line = NULL;
	reset_options(shell);
	reset_fd(shell);
	close_fd(shell);
	reset_stds(shell);
}

int		error_exit(int error, char *error_msg)
{
	ft_printf_fd(2, "%s\n", error_msg);
	return (error);
}

int		is_from(char c, char *chars)
{
	int i;

	i = 0;
	while (chars[i])
	{
		if (c == chars[i])
			return (1);
		i++;
	}
	return (0);
}

void	lst_malloc(void **to_malloc, size_t size, t_data *shell)
{
	t_list *new;

	if (!(*to_malloc = ft_calloc(1, size)))
		return ;
	if (!(new = ft_lstnew(*to_malloc)))
		return ;
	ft_lstadd_front(&(shell->trash), new);
}

int		ft_argisnum(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
