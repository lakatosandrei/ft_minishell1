/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnextline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakatos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/17 14:34:08 by alakatos          #+#    #+#             */
/*   Updated: 2014/12/14 20:36:29 by alakatos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_realloc(char *ptr, char *copy, size_t size)
{
	char	*new;
	int		len;

	len = 0;
	if (ptr)
		len = ft_strlen(ptr) + 1;
	new = 0;
	new = (char *)ft_memalloc(size + len);
	if (ptr)
		ft_strlcat(new, ptr, len + 1);
	ft_strcat(new, copy);
	free(ptr);
	return (new);
}

int		find_new(char *buf)
{
	size_t i;

	i = 0;
	while (buf[i])
	{
		if (buf[i++] == '\n')
			return (i - 1);
	}
	return (BUFF_SIZE);
}

char	*treat_previous(char *previous, char **line)
{
	int		aux;

	if (*line)
		(*line) = ft_strnew(100000);
	if (previous)
	{
		aux = find_new(previous) + 1;
		ft_strlcpy(*line, previous, aux);
		if (aux - 1 != BUFF_SIZE)
		{
			previous = previous + aux;
			return (previous);
		}
	}
	return (0);
}

int		get_next_line(int const fd, char **line)
{
	static char	**previous;
	char		*buf;
	int			len;
	int			aux;

	buf = ft_strnew(BUFF_SIZE + 1);
	if (!previous)
		previous = (char **)ft_memalloc(sizeof(char *) * 1000);
	previous[fd] = treat_previous((char *)previous[fd], line);
	if (previous[fd])
		return (1);
	while ((len = read(fd, buf, BUFF_SIZE)))
	{
		aux = find_new(buf) + 1;
		ft_strlcat(*line, buf, ft_strlen(*line) + aux);
		if (aux - 1 != BUFF_SIZE)
		{
			previous[fd] = ft_realloc(previous[fd], buf + aux, len - aux + 1);
			return (1);
		}
	}
	return (len);
}
