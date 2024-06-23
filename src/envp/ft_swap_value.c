/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:44:06 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/23 14:17:24 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_envp_value(const char *key, t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (tmp->value == NULL)
				return (ft_strdup(""));
			return (ft_strdup(tmp->value));
		}
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

char	*ft_swap_value(char *line, int start, int end, t_env *envp)
{
	char	*key;
	char	*value;
	char	*new_line;

	key = NULL;
	value = NULL;
	new_line = NULL;
	key = ft_substr(line, start + 1, end - start);
	value = ft_get_envp_value(key, envp);
	value = ft_special_quote(value);
	new_line = ft_strunion(line, value, start, end);
	if (key != NULL)
		free(key);
	if (value != NULL)
		free(value);
	if (line != NULL)
		free(line);
	return (new_line);
}
