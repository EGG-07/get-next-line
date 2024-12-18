/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aces-sal <aces-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 01:32:35 by aces-sal          #+#    #+#             */
/*   Updated: 2024/12/18 04:32:45 by aces-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*next_new_line(int fd, char *next_start, char *buff)
{
	ssize_t	byte_read;
	char	*tmp;

	byte_read = 1;
	while (byte_read > 0 && !ft_strchr(buff, '\n'))
	{
		byte_read = read(fd, buff, BUFFER_SIZE);
		if (byte_read == (-1))
		{
			free(next_start);
			return (NULL);
		}
		if (byte_read == 0)
			return (next_start);
		buff[byte_read] = '\0';
		tmp = next_start;
		if (tmp)
			next_start = ft_strjoin(tmp, buff);
		else
			next_start = ft_strdup(buff);
		free(tmp);
		if (!next_start)
			return (NULL);
	}
	return (next_start);
}

static char	*chr_new_line(char *line)
{
	char	*next_start;
	size_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (NULL);
	next_start = ft_substr(line, i + 1, ft_strlen(line) - i - 1);
	if (next_start && *next_start == '\0')
	{
		free(next_start);
		next_start = NULL;
	}
	line[i + 1] = '\0';
	return (next_start);
}

char	*get_next_line(int fd)
{
	static char	*next_start;
	char		*line;
	char		*buff;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	line = next_new_line(fd, next_start, buff);
	free(buff);
	if (!line)
	{
		free(next_start);
		next_start = NULL;
		return (NULL);
	}
	if (ft_strchr(line, '\n'))
		next_start = chr_new_line(line);
	else
		next_start = NULL;
	return (line);
}
