/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:07:12 by fdonati           #+#    #+#             */
/*   Updated: 2024/05/16 14:57:19 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_read(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*tmp;
	int			ret;

	if (buffer[0] == '\0')
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret < 0)
			return (NULL);
		buffer[ret] = '\0';
	}
	tmp = malloc(sizeof(char) * get_strlen(buffer) + 1);
	get_strlcpy(tmp, buffer, get_strlen(buffer) + 1);
	if (get_strchr(buffer, '\n') != NULL)
		get_strlcpy(buffer, get_strchr(buffer, '\n') + 1, BUFFER_SIZE + 1);
	else
		buffer[0] = '\0';
	return (tmp);
}

static char	*get_lines(char *line, int fd)
{
	char		*buffer;
	char		*tmp;

	while (get_strchr(line, '\n') == NULL)
	{
		buffer = get_read(fd);
		if (buffer == NULL)
		{
			free(line);
			return (NULL);
		}
		tmp = line;
		line = get_strljoin(line, buffer);
		free(tmp);
		if (line == NULL)
			return (NULL);
		if (*buffer == '\0')
		{
			free(buffer);
			break ;
		}
		free(buffer);
	}
	return (line);
}

char	*ft_get_next_line(int fd)
{
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(sizeof(char));
	if (line == NULL)
		return (NULL);
	*line = '\0';
	line = get_lines(line, fd);
	if (line == NULL)
		return (NULL);
	if (*line == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/* static char	*ft_remainder_trim(char *remainder)
{
	size_t	remainder_index;
	size_t	line_index;
	char	*line;

	remainder_index = 0;
	line_index = 0;
	while (remainder[remainder_index] != '\n' && remainder[remainder_index])
		remainder_index++;
	if (!remainder[remainder_index])
	{
		free(remainder);
		return (NULL);
	}
	line = ft_calloc(ft_strlen(remainder) - remainder_index + 1, sizeof(char));
	remainder_index++;
	while (remainder[remainder_index])
		line[line_index++] = remainder[remainder_index++];
	free(remainder);
	return (line);
}

static char	*ft_get_line(char *remainder)
{
	char	*line;
	size_t	index;

	index = 0;
	if (!remainder[index])
		return (NULL);
	while (remainder[index] != '\n' && remainder[index])
		index++;
	line = ft_calloc(index + 2, sizeof(char));
	index = 0;
	while (*remainder != '\n' && *remainder)
		line[index++] = *remainder++;
	if (*remainder == '\n')
		line[index] = '\n';
	return (line);
}

static char	*ft_read_line(int fd, char *remainder)
{
	char	*temp_remainder;
	char	*read_remainder;
	ssize_t	bytes_read;

	if (!remainder)
		remainder = ft_calloc(1, sizeof(char));
	temp_remainder = remainder;
	read_remainder = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1;
	while (!ft_strchr(remainder, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, read_remainder, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(read_remainder);
			free(temp_remainder);
			return (NULL);
		}
		read_remainder[bytes_read] = '\0';
		temp_remainder = remainder;
		remainder = ft_strjoin(temp_remainder, read_remainder);
	}
	free(read_remainder);
	return (remainder);
}

char	*ft_get_next_line(int fd)
{
	char		*line;
	static char	*remainder[FD_MAX];

	if (fd == -1 || BUFFER_SIZE <= 0 || fd >= FD_MAX)
		return (NULL);
	remainder[fd] = ft_read_line(fd, remainder[fd]);
	if (!remainder[fd])
		return (NULL);
	line = ft_get_line(remainder[fd]);
	remainder[fd] = ft_remainder_trim(remainder[fd]);
	return (line);
} */

/*****************************************************************************/
/*						MAIN												 */
/*****************************************************************************
#include <stdio.h>

void	print_hex(char *str)
{
	while (*str)
	{
		printf("%02hhx ", *str);
		str++;
	}
	printf("\n");
}

int	main(int argc, char **argv)
{
	int		fds[argc - 1];
	char	*line;
	int		i;

	if (argc < 2)
	{
		printf("Uso: %s <file1> [<file2> ...]\n", argv[0]);
		return (1);
	}
	for (i = 1; i < argc; i++)
	{
		fds[i - 1] = open(argv[i], O_RDONLY);
		if (fds[i - 1] == -1)
		{
			perror("Errore nell'apertura del file");
			return (2);
		}
	}
	for (i = 0; i < argc - 1; i++)
	{
		printf("=== Contenuto del file: %s ===\n", argv[i + 1]);
		while ((line = get_next_line(fds[i])) != NULL)
		{
			print_hex(line);
			free(line);
		}
		printf("\n\n");
		if (close(fds[i]) == -1)
		{
			perror("Errore nella chiusura del file");
			return (3);
		}
	}
	return (0);
}
*/