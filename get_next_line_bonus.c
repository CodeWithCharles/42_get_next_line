/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:02:04 by cpoulain          #+#    #+#             */
/*   Updated: 2024/10/30 12:15:18 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Includes */

#include "get_next_line_bonus.h"

/* Static declarations */

char	*_read_from_fd_to_line(int fd, char *buffer);
char	*_process_leftover_buffer(char *buffer);
void	_process_buffer_into_line(char **line, char *buffer);

/* get_next_line */

char	*get_next_line(int fd)
{
	static char	fd_buffers[FD_LIMIT][BUFFER_SIZE + 1] = {0};
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	line = _read_from_fd_to_line(fd, fd_buffers[fd]);
	if (line == NULL)
		return (NULL);
	if (ft_strlen(line) == 0)
		return (free(line), NULL);
	return (line);
}

/* Static implementation */

void	_process_buffer_into_line(char **line, char *buffer)
{
	char	*nl_pos;
	size_t	remaining_buffer;
	char	saved_char;

	nl_pos = ft_strchr(buffer, '\n');
	if (nl_pos)
	{
		saved_char = nl_pos[1];
		nl_pos[1] = '\0';
		ft_strcat(line, buffer);
		if (*line == NULL)
			return ;
		nl_pos[1] = saved_char;
		nl_pos++;
	}
	else
	{
		ft_strcat(line, buffer);
		if (*line == NULL)
			return ;
		nl_pos = buffer + ft_strlen(buffer);
	}
	remaining_buffer = ft_strlen(nl_pos);
	ft_memcpy(buffer, nl_pos, remaining_buffer);
	buffer[remaining_buffer] = '\0';
}

char	*_process_leftover_buffer(char *buffer)
{
	char	*line;
	size_t	line_size;

	line = ft_strchr(buffer, '\n');
	if (line == NULL)
		line = ft_strchr(buffer, '\0');
	line_size = line - buffer + (*line == '\n');
	line = (char *) malloc(line_size + 1);
	if (line == NULL)
		return (NULL);
	ft_memcpy(line, buffer, line_size);
	line[line_size] = '\0';
	ft_memcpy(buffer, buffer + line_size, BUFFER_SIZE - line_size);
	buffer[BUFFER_SIZE - line_size] = '\0';
	return (line);
}

char	*_read_from_fd_to_line(int fd, char *buffer)
{
	char	*line;
	long	byte_read;

	line = _process_leftover_buffer(buffer);
	if (line == NULL)
		return (NULL);
	while (!ft_strchr(line, '\n'))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
			return (free(line), NULL);
		buffer[byte_read] = '\0';
		if (byte_read == 0 || ft_strchr(buffer, '\n'))
			return (_process_buffer_into_line(&line, buffer), line);
		ft_strcat(&line, buffer);
		if (line == NULL)
			return (NULL);
	}
	return (line);
}
