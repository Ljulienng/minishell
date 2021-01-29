/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:27:19 by jnguyen           #+#    #+#             */
/*   Updated: 2021/01/29 17:45:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

static int			newline_check(char *stock, int read_size)
{
	int	i;

	i = 0;
	if (read_size == 0 && stock[0] == '\0')
		return (2);
	if (read_size == 0 || stock == NULL)
		return (0);
	while (stock[i] != '\0')
	{
		if (stock[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static int			ft_strchr_gnl(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
			return (-1);
		i++;
	}
	return (i);
}

static char			*strjoingnl(char const *s1, char const *s2, unsigned int n)
{
	int				i;
	int				j;
	int				size;
	char			*dest;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		size = 0;
	else
		size = ft_strlen(s1) + ft_strlen(s2);
	if (!(dest = ft_calloc(1, sizeof(char) * size + 1)))
		return (NULL);
	while (s1[i] != '\0')
		dest[j++] = s1[i++];
	i = 0;
	while (s2[i] && n > 0)
	{
		dest[j++] = s2[i++];
		n--;
	}
	dest[j] = '\0';
	free((void*)s1);
	return (dest);
}

int					get_next_line(int fd, char **line)
{
	static char		buffer[4097];
	char			buffer_temp[1];
	int				ret;
	int				ret2;

	ret = 1;
	if (fd <= -1 || line == NULL || (read(fd, buffer_temp, 0) < 0))
		return (-1);
	*line = ft_strdup("");
	while (ret && (ret2 = ft_strchr_gnl(buffer, '\n')) == -1)
	{
		if (!(*line = strjoingnl(*line, buffer, 4096)))
			return (-1);
		if ((ret = read(fd, buffer, 4096)) == -1)
			return (-1);
		buffer[ret] = 0;
		(ret == 0 || buffer[ret - 1] != '\n') ? ft_printf("  \b\b") : 0;
	}
	if (newline_check(*line, ret) == 2)
		return (-2);
	if (!(*line = strjoingnl(*line, buffer, ret2)))
		return (-1);
	if (ret)
		ft_strcpy(buffer, &buffer[ret2 + 1]);
	return (1);
}
