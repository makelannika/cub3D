/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:03:07 by amakela           #+#    #+#             */
/*   Updated: 2024/10/29 00:22:22 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../../include/cub3d.h"

char	*set_err(int *flag)
{
	*flag = 1;
	return (NULL);
}

int	free_ptr(char **ptr)
{
	if (!*ptr)
		return (-1);
	free(*ptr);
	*ptr = NULL;
	return (-1);
}

char	*get_line(t_gnl *gnl, ssize_t bytes_read, char **line)
{
	int		i;
	char	*tmp;

    i = 0;
    while(gnl->text_read[i] != '\n' && gnl->text_read[i] != '\0')
        i++;
    if (gnl->text_read[i] == '\n')
        i++;
    if (!i)
        return (NULL);
    *line = ft_substr(gnl->text_read, 0, i);
    if (!*line)
        return (set_err(&gnl->err));
    if(!bytes_read)
        return (*line);
    tmp = gnl->text_read;
    gnl->text_read = ft_substr(gnl->text_read, i, ft_strlen(gnl->text_read) - i);
    free_ptr(&tmp);
    if (!gnl->text_read)
    {
        free_ptr(line);
        return (set_err(&gnl->err));
    }
    return (*line);
}

ssize_t	read_file(t_gnl *gnl, ssize_t *bytes_read, int fd)
{
	char	*tmp;
	char	buffer[BUFFER_SIZE + 1];

	while (!ft_strchr(gnl->text_read, '\n') && *bytes_read)
	{
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*bytes_read == -1)
			return (free_ptr(&gnl->text_read));
		buffer[*bytes_read] = '\0';
		tmp = gnl->text_read;
		gnl->text_read = ft_strjoin(gnl->text_read, buffer);
		free_ptr(&tmp);
		if (!gnl->text_read)
			return (-1);
	}
	return (*bytes_read);
}

char	*get_next_line(t_gnl *gnl)
{
	char		*line;
	ssize_t		bytes_read;

    line = NULL;
    bytes_read = 1;
    if (!gnl->text_read)
        gnl->text_read = ft_calloc(1, 1);
    if (!gnl->text_read)
        return (set_err(&gnl->err));
    if (read_file(gnl, &bytes_read, gnl->fd) == -1)
        return (set_err(&gnl->err));
    if (!get_line(gnl, bytes_read, &line) || !bytes_read)
        free_ptr(&gnl->text_read);
    if (!line)
        return (NULL);
    return (line);
}
