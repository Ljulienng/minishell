/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:11:19 by user42            #+#    #+#             */
/*   Updated: 2021/02/02 16:32:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_arg			*next_run(t_arg *arg, int skip)
{
	if (arg && skip)
		arg = arg->next;
	while (arg && arg->type != CMD)
	{
		arg = arg->next;
		if (arg && arg->type == CMD && arg->prev == NULL)
			;
		else if (arg && arg->type == CMD && arg->prev->type != SEMI_C)
			arg = arg->next;
	}
	return (arg);
}

static void		arglist_type(t_arg *current)
{
	if (ft_strcmp(current->str, "") == 0)
		current->type = NONE;
	else if (ft_strcmp(current->str, ">") == 0)
		current->type = R_ANGLE;
	else if (ft_strcmp(current->str, ">>") == 0)
		current->type = D_ANGLE;
	else if (ft_strcmp(current->str, "<") == 0)
		current->type = L_ANGLE;
	else if (ft_strcmp(current->str, "|") == 0)
		current->type = PIPE;
	else if (ft_strcmp(current->str, ";") == 0)
		current->type = SEMI_C;
	else if (current->prev == NULL || (current->prev->type >= SEMI_C
	&& current->prev->type <= PIPE))
		current->type = CMD;
	else
		current->type = ARG;
}

void			arg_listclear(t_arg *lst)
{
	t_arg	*current;
	t_arg	*next;

	current = lst;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	lst = NULL;
}

static void		add_arglist(char *arg, t_data *shell)
{
	t_arg	*current;
	t_arg	*next;

	current = shell->arg_list;
	if (!(next = malloc(sizeof(t_arg))))
		return ;
	while (current != NULL)
	{
		if (current->next == NULL)
			break ;
		current = current->next;
	}
	current->next = next;
	next->str = arg;
	next->prev = current;
	next->next = NULL;
}

void			set_arglist(t_data *shell)
{
	int		i;
	t_arg	*current;
	t_arg	*next;

	if (!(shell->arg_list = malloc(sizeof(t_arg))))
		return ;
	shell->arg_list->str = shell->arg[0];
	shell->arg_list->next = NULL;
	shell->arg_list->prev = NULL;
	i = 1;
	while (shell->arg[i])
	{
		add_arglist(shell->arg[i], shell);
		i++;
	}
	current = shell->arg_list;
	while (current)
	{
		next = current->next;
		arglist_type(current);
		current = next;
	}
}
