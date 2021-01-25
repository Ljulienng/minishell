/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 13:47:34 by user42            #+#    #+#             */
/*   Updated: 2021/01/22 13:48:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_next_cmd(t_data *shell)
{
	shell->params.old_index = 0;
	shell->params.arg_index = 0;
	close_fd(shell);
	reset_fd(shell);
	reset_stds(shell);
	shell->params.semicolon--;
	process_semicolon(shell, 0);
	redir_cmd(shell, 0);
	if (((shell->params.child && !shell->params.parent) \
	|| (!shell->params.child \
	&& !shell->params.parent)) && shell->params.semicolon && shell->pid == -1)
		do_next_cmd(shell);
}

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
