/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:54:56 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/20 16:40:22 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_join_value(t_env *tmp, char *value)
{
	char	*new_value;

	if (value == NULL)
		return (1);
	if (tmp->value == NULL)
	{
		tmp->value = ft_strdup(value);
		if (!tmp->value)
			return (-1);
		return (1);
	}
	new_value = ft_strjoin(tmp->value, value);
	free(tmp->value);
	if (new_value == NULL)
		return (-1);
	tmp->value = new_value;
	return (1);
}

static int	ft_new_value(t_env *tmp, char *value)
{
	if (value == NULL)
		return (1);
	free(tmp->value);
	tmp->value = ft_strdup(value);
	if (!tmp->value)
		return (-1);
	return (1);
}

int	ft_change_value(t_env **env, char *key, char *value, int flag)
{
	t_env	*tmp;

	tmp = *env;
	if (key == NULL)
		return (0);
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (flag == 0)
				return (ft_new_value(tmp, value));
			if (flag == 1)
				return (ft_join_value(tmp, value));
		}
		tmp = tmp->next;
	}
	return (0);
}
