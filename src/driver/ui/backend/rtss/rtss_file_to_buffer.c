/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_file_to_buffer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:41:41 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/06 14:28:52 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <libft.h>
#include <stdbool.h>

static bool __rtss_check_file_format(const char *filename)
{
	const char *extension;

	if (!filename)
		return (false);
	extension = ft_strchr(filename, '.');
    return (extension && ft_strcmp(extension, ".rtss") == 0);
}

static int __rtss_open_file(const char *filename)
{
	int fd;

	if (!__rtss_check_file_format(filename))
	{
		ft_putstr_fd("RTSS Error: invalid file format\n", 2);
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	return (fd);
}

static long __rtss_get_file_size(int fd)
{
	long filesize;

	filesize = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	return (filesize);
}

static char *__read_fd_in_str(int fd, long filesize)
{
	char *str_file;
	ssize_t bytes_read;

	str_file = malloc((filesize + 1) * sizeof(char));
	if (!str_file)
	{
		ft_putstr_fd("RTSS Error: imposible to allocate the file\n", 2);
		close(fd);
		return (NULL);
	}
	bytes_read = read(fd, str_file, filesize);
	if (bytes_read == -1)
	{
		ft_putstr_fd("RTSS Error: imposible to read the file\n", 2);
		free(str_file);
		str_file = NULL;
	}
	else
		str_file[filesize] = 0;
	close(fd);
	return (str_file);
}

char *rtss_file_to_buffer(const char *filename)
{
	int fd;
	long filesize;

	fd = __rtss_open_file(filename);
	if (fd == -1)
		return (NULL);
	filesize = __rtss_get_file_size(fd);
	if (filesize == -1)
	{
		ft_putstr_fd("RTSS Error: imposible to get the file size\n", 2);
		close(fd);
		return (NULL);
	}
	return (__read_fd_in_str(fd, filesize));
}
