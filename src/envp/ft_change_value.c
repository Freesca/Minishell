/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:54:56 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/06 15:35:58 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_change_value(t_env *env, char *key, char *value)
{
	t_env	*tmp;

	tmp = env;
	if (key == NULL)
		return (0);
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (value == NULL)
				return (1);
			free(tmp->value);
			tmp->value = ft_strdup(value);
			if (!tmp->value)
				return (-1);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
