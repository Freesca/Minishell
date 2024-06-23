/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_envp_hc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:54:01 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/23 14:57:28 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_swap_value_hc(char *line, int start, int end, t_env *envp)
{
	char	*key;
	char	*value;
	char	*new_line;

	key = NULL;
	value = NULL;
	new_line = NULL;
	key = ft_substr(line, start + 1, end - start);
	value = ft_get_envp_value(key, envp);
	new_line = ft_strunion(line, value, start, end);
	if (key != NULL)
		free(key);
	if (value != NULL)
		free(value);
	if (line != NULL)
		free(line);
	return (new_line);
}

static char	*ft_process_env_var_hc(char *line, int start, int *i, t_env *envp)
{
	line = ft_swap_value_hc(line, start, (*i) - 1, envp);
	*i = start;
	return (line);
}

char	*ft_swap_scroll_hc(char *line, int *i, t_env *envp, int flag_lim)
{
	int	start;

	start = 0;
	if (line[*i] == '$')
	{
		start = (*i)++;
		if (ft_isalnum(line[*i]) == 1
			|| (line[*i] == '?' && line[*i] != '\0'))
		{
			ft_find_env_var_end(line, i);
			if (flag_lim == 0)
				line = ft_process_env_var_hc(line, start, i, envp);
		}
	}
	else if (line != NULL && line[*i] != '\0')
		(*i)++;
	return (line);
}

char	*ft_swap_envp_hc(char *line, t_env *envp)
{
	int	i;

	i = 0;
	while (line != NULL && line[i] != '\0')
	{
		if (line[i] == '\'')
			i = ft_skip_single_quotes(line, i);
		line = ft_swap_scroll_hc(line, &i, envp, 0);
	}
	return (line);
}
