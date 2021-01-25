/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 20:12:33 by julienngy         #+#    #+#             */
/*   Updated: 2020/12/07 16:01:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*next;

	current = *lst;
	if (lst == NULL || del == NULL)
		return ;
	while (current)
	{
		next = current->next;
		if (current->content != NULL)
		{
			(*del)(current->content);
			free(current);
		}
		current = next;
	}
	*lst = NULL;
}
