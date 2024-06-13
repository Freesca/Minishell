/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:21:31 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/13 11:28:20 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_quote_clean(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			str = ft_strfrmv(str, i);
			if (str == NULL)
				return (NULL);
			while (str[i] != quote && str[i] != '\0')
				i++;
			str = ft_strfrmv(str, i);
			if (str == NULL)
				return (NULL);
		}
		if (str[i] != '\'' && str[i] != '\"' && str[i] != '\0')
			i++;
	}
	return (str);
}
