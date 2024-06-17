/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_envp_hc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:54:01 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/14 00:45:35 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_swap_scroll_hc(char *line, int *i, t_env *envp)
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
			line = ft_process_env_var(line, start, i, envp);
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
		line = ft_swap_scroll_hc(line, &i, envp);
	}
	return (line);
}
