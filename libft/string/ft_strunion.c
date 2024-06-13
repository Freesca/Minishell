/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strunion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:56:00 by fdonati           #+#    #+#             */
/*   Updated: 2024/05/28 15:16:12 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strunion_util(char *dst, char *src, int *i, int *j)
{
	dst[*j] = src[*i];
	(*i)++;
	(*j)++;
}

char	*ft_strunion(char *line, char *value, int start, int end)
{
	char	*new_line;
	int		i;
	int		j;

	if (line == NULL || value == NULL)
		return (NULL);
	if (start < 0 || end < 0 || start > end
		|| start >= (int) ft_strlen(line) || end >= (int) ft_strlen(line))
		return (NULL);
	new_line = malloc(ft_strlen(line) + ft_strlen(value) - (end - start));
	if (new_line == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i] != '\0' && i < start)
		ft_strunion_util(new_line, line, &i, &j);
	i = 0;
	while (value[i] != '\0')
		ft_strunion_util(new_line, value, &i, &j);
	i = end + 1;
	while (line[i] != '\0')
		ft_strunion_util(new_line, line, &i, &j);
	new_line[j] = '\0';
	return (new_line);
}

/* int	main()
{
	char	*line = "Hello, $USER!";
	char	*value = "World";
	int		start = 7;
	int		end = 12;

	char	*new_line = ft_strunion(line, value, start, end);
	ft_printf(1, "ft_strunion(\"%s\", \"%s\", %d, %d) = \"%s\"\n", line, value, start, end, new_line);
} */
