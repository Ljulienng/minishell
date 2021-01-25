/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 20:39:40 by user42            #+#    #+#             */
/*   Updated: 2021/01/21 20:39:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnjoin(char *s1, char const *s2, size_t n)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	j = 0;
	while (s1 != NULL && s1[i] != '\0')
		i++;
	while (s2[j] != '\0' && j < n)
		j++;
	if ((res = (char*)malloc(sizeof(char) * (i + j + 10))))
	{
		i = 0;
		j = -1;
		while (s1 != NULL && s1[i] != '\0')
		{
			res[i] = s1[i];
			i++;
		}
		while (s2[++j] != '\0' && n--)
			res[i + j] = s2[j];
		res[i + j] = '\0';
	}
	free(s1);
	return (res);
}
