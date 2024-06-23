/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:14:04 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/23 17:17:34 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_skip_single_quotes(const char *line, int i)
{
	i++;
	while (line[i] != '\0' && line[i] != '\'')
		i++;
	return (i);
}

void	ft_find_env_var_end(const char *line, int *i)
{
	if (line[*i] == '?' || ft_isdigit(line[*i]) == 1)
	{
		(*i)++;
		return ;
	}
	while (line[*i] != '\0'
		&& (ft_isalnum(line[*i]) == 1 || line[*i] == '_'))
		(*i)++;
	return ;
}

char	*ft_process_env_var(char *line, int start, int *i, t_env *envp)
{
	line = ft_swap_value(line, start, (*i) - 1, envp);
	*i = start;
	return (line);
}

static char	*ft_swap_scroll(char *line, int *i, t_env *envp, int flag_lim)
{
	int	start;

	start = 0;
	if (line[*i] == '$')
	{
		start = (*i)++;
		if (ft_isalnum(line[*i]) == 1 || line[*i] == '_'
			|| (ft_strchr("?\'\"", line[*i]) != NULL && line[*i] != '\0'))
		{
			ft_find_env_var_end(line, i);
			if (flag_lim == 0)
				line = ft_process_env_var(line, start, i, envp);
		}
	}
	else if (line != NULL && line[*i] != '\0')
		(*i)++;
	return (line);
}

char	*ft_swap_envp(char *line, t_env *envp)
{
	int	i;
	int	flag_dquote;
	int	flag_lim;

	i = 0;
	flag_dquote = 0;
	flag_lim = 0;
	while (line != NULL && line[i] != '\0')
	{
		if (line[i] == '<' && line[i + 1] == '<')
			flag_lim++;
		if (line[i] == '\'' && flag_dquote % 2 == 0)
			i = ft_skip_single_quotes(line, i);
		if (line[i] == '\"')
			flag_dquote++;
		if (flag_dquote % 2 == 0)
			line = ft_swap_scroll(line, &i, envp, flag_lim);
		else
			line = ft_swap_scroll_hc(line, &i, envp, flag_lim);
		if (line != NULL
			&& ft_strchr(" \t|><", line[i]) != NULL && i > 0
			&& ft_strchr(" \t|><", line[i - 1]) == NULL)
			flag_lim = 0;
	}
	return (line);
}
