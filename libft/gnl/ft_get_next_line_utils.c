/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:18:12 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/23 16:19:37 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	get_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	get_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	n;
	size_t	i;

	n = get_strlen(src);
	i = 0;
	if (size == 0)
		return (n);
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (n);
}

size_t	get_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	i = 0;
	src_len = get_strlen(src);
	dst_len = get_strlen(dst);
	while (dst_len + i + 1 < size && src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	if (dst_len + i < size)
	{
		dst[dst_len + i] = '\0';
		return (src_len + dst_len);
	}
	else
		return (src_len + size);
}

char	*get_strchr(const char *s, int c)
{
	char	*str;

	str = (char *) s;
	while (*str != '\0')
	{
		if ((char) c == *str)
			return ((char *) str);
		str++;
	}
	if ((char) c == *str)
		return ((char *) str);
	return (NULL);
}

char	*get_strljoin(const char *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	s1_len = get_strlen(s1);
	s2_len = 0;
	while (s2[s2_len] != '\0')
	{
		s2_len++;
		if (s2[s2_len - 1] == '\n')
			break ;
	}
	str = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	get_strlcpy(str, s1, s1_len + 1);
	get_strlcat(str, s2, s1_len + s2_len + 1);
	return (str);
}
