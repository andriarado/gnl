/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randriat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 07:07:05 by randriat          #+#    #+#             */
/*   Updated: 2024/03/28 06:28:16 by randriat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static size_t	find_start_end(char *buf)
{
	size_t	i;

	i = 0;
	while (buf[i] != '\n' && buf[i])
		i++;
	if (buf[i] == '\n')
		i++;
	return (i);
}

static char	*update_buf(char *buf)
{
	char	*new_buf;
	size_t	i;
	size_t	j;

	i = find_start_end(buf);
	new_buf = (char *)malloc((ft_strlen(buf) - i) + 1);
	if (!new_buf)
	{
		free(buf);
		return (NULL);
	}	
	j = 0;
	while (buf[i])
		new_buf[j++] = buf[i++];
	new_buf[j] = '\0';
	if (!*new_buf)
	{
		free(buf);
		free(new_buf);
		return (NULL);
	}
	free(buf);
	return (new_buf);
}

static char	*create_line(char *buf)
{
	char	*line;
	size_t	i;
	size_t	end;

	if (!buf || *buf == '\0')
		return (NULL);
	end = 0;
	while (buf[end] && buf[end] != '\0')
		end++;
	line = (char *)malloc(sizeof(char) * (end + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
	{
		line[i] = buf[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_free(char *buf, char *line)
{
	free(buf);
	free(line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	int			vl_read;
	static char	*buf;

	vl_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	while (!(ft_strchr(buf, '\n')) && vl_read != 0)
	{
		vl_read = read(fd, line, BUFFER_SIZE);
		if (vl_read == -1)
		{
			buf = ft_free(buf, line);
			return (NULL);
		}
		line[vl_read] = '\0';
		buf = ft_strjoin(buf, line);
	}
	free(line);
	line = create_line(buf);
	buf = update_buf(buf);
	return (line);
}
