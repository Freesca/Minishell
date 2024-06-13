/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:14:04 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/13 20:38:37 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_skip_single_quotes(const char *line, int i)
{
	i++;
	while (line[i] != '\'' && line[i] != '\0')
		i++;
	return (i);
}

static int	ft_find_env_var_end(const char *line, int i)
{
	while (line[i] != '\0'
		&& (ft_isalnum(line[i]) == 1 || line[i] == '?')
		&& (line[i - 1] != '?'
			&& ft_isdigit(line[i - 1]) == 0))
		i++;
	return (i);
}

static char	*ft_process_env_var(char *line, int start, int *i, t_env *envp)
{
	line = ft_swap_value(line, start, *i - 1, envp);
	*i = start;
	return (line);
}

char	*ft_swap_envp_hc(char *line, t_env *envp)
{
	int	i;
	int	start;

	i = 0;
	while (line != NULL && line[i] != '\0')
	{
		if (line[i] == '\'')
			i = ft_skip_single_quotes(line, i);
		else if (line[i] == '$')
		{
			start = i++;
			if (ft_isalnum(line[i]) == 1
				|| (line[i] == '?' && line[i] != '\0'))
			{
				i = ft_find_env_var_end(line, i);
				line = ft_process_env_var(line, start, &i, envp);
			}
		}
		else if (line[i] != '\0')
			i++;
	}
	return (line);
}

char	*ft_swap_envp(char *line, t_env *envp)
{
	int	i;
	int	start;

	i = 0;
	while (line != NULL && line[i] != '\0')
	{
		if (line[i] == '\'')
			i = ft_skip_single_quotes(line, i);
		else if (line[i] == '$')
		{
			start = i++;
			if (ft_isalnum(line[i]) == 1
				|| (ft_strchr("?\'\"", line[i]) != NULL && line[i] != '\0'))
			{
				i = ft_find_env_var_end(line, i);
				line = ft_process_env_var(line, start, &i, envp);
			}
		}
		else if (line[i] != '\0')
			i++;
	}
	return (line);
}

char	*ft_swap_envp(char *line, char **envp)
{
	int	i;
	int	start;

	i = 0;
	while (line != NULL && line[i] != '\0')
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'' && line[i] != '\0')
				i++;
		}
		else if (line[i] == '$')
		{
			start = i++;
			if (ft_strchr(" \t", line[i]) == NULL)
			{
				while (line[i] != '\0'
					&& ft_strchr(" \t\n$\"\'|><", line[i]) == NULL
					&& line[i - 1] != '?')
					i++;
				line = ft_swap_value(line, start, i - 1, envp);
				i = start + 1;
			}
		}
		else
			i++;
	}
	return (line);
}
