/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfrmv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:13:20 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/23 16:20:10 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfrmv(char *str, size_t index)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (str == NULL)
		return (NULL);
	if (index >= ft_strlen(str))
		return (str);
	new = malloc(sizeof(char) * ft_strlen(str));
	if (new == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (i == index)
			i++;
		if (str[i] == '\0')
			break ;
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (free(str), new);
}

/* int	main(void)
{
	char	*str;

	str = ft_strdup("'Goku and v'egeta");
	printf("Before: %s<\n", str);
	str = ft_strfrmv(str, 0);
	printf("After: %s<\n", str);
	free(str);
	return (0);
} */