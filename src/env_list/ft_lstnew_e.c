/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_e.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:57:22 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/20 16:31:22 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_key_n_value(char *str, char **key, char **value)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=' && str[i] != '+')
		i++;
	*key = ft_substr(str, 0, i);
	if (!*key)
		return (-1);
	if (ft_strchr(str, '=') != NULL)
	{
		if (str[i] == '+')
			i++;
		*value = ft_strdup(str + i + 1);
		if (!*value)
		{
			free(*key);
			return (-1);
		}
	}
	else
		*value = NULL;
	return (1);
}

t_env	*ft_lstnew_e(char *str, t_env_type type)
{
	t_env	*new;
	int		ret;

	ret = 0;
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	ret = ft_key_n_value(str, &new->key, &new->value);
	if (ret == -1)
	{
		free(new);
		return (NULL);
	}
	new->type = type;
	return (new);
}
