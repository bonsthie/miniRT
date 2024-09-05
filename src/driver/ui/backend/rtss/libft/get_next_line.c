/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:33:50 by bbonnet           #+#    #+#             */
/*   Updated: 2024/07/18 13:48:59 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	strlen_char(const char *str, const char c)
{
	const char	*start;

	if (str == NULL)
		return (0);
	start = str;
	while (*start && *start != c)
		++start;
	return (start - str + (*start == c));
}

int	extract_line_from_buffer(char **line, char *buffer, int *line_len)
{
	int		buffer_len;
	char	*new_line;

	buffer_len = strlen_char(buffer, '\n');
	if (buffer_len == 0)
		return (0);
	*line_len += buffer_len;
	new_line = ft_realloc_str(*line, (*line_len + 1));
	if (!new_line)
		return (-1);
	if (*line == NULL)
		new_line[0] = 0;
	ft_strlcat(new_line, buffer, *line_len + 1);
	new_line[*line_len] = '\0';
	*line = new_line;
	if (buffer[buffer_len - 1] == '\n')
	{
		ft_memmove(buffer, buffer + buffer_len, ft_strlen(buffer) - buffer_len
			+ 1);
		return (1);
	}
	buffer[0] = 0;
	return (2);
}

int	add_to_buffer(int fd, char *buffer, char **line)
{
	int	read_bytes;

	read_bytes = 0;
	if (buffer[0] == 0)
		read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (read_bytes < 0)
		return (-1);
	buffer[read_bytes] = 0;
	if (read_bytes == 0)
	{
		if (line == NULL || *line == 0)
			return (-1);
		return (1);
	}
	return (0);
}

char	*return_line(char *buffer, int fd)
{
	char	*line;
	int		line_len;
	int		status;

	line = NULL;
	line_len = 0;
	while (1)
	{
		status = extract_line_from_buffer(&line, buffer, &line_len);
		if (status == 1)
			return (line);
		else if (status == -1)
		{
			free(line);
			line = NULL;
			return (NULL);
		}
		status = add_to_buffer(fd, buffer, &line);
		if (status == -1)
			return (NULL);
		if (status == 1)
			return (line);
	}
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer[fd] == NULL)
	{
		buffer[fd] = (char *)malloc(BUFFER_SIZE + 1);
		if (buffer[fd] == NULL)
			return (NULL);
		buffer[fd][0] = '\0';
	}
	line = return_line(buffer[fd], fd);
	if (buffer[fd][0] == 0)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (line);
}
