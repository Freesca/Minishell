/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:18:53 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/13 11:45:39 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_single_quote(char *line, int *i)
{
	(*i)++;
	while (line[*i] != '\'' && line[*i] != '\0')
		(*i)++;
	if (line[*i] == '\0')
	{
		ft_printf(2, "minishell: syntax error: open quote not supported\n");
		return (-1);
	}
	if (line[*i] == '\'')
		(*i)++;
	return (0);
}

static int	ft_double_quote(char *line, int *i)
{
	(*i)++;
	while (line[*i] != '\"' && line[*i] != '\0')
		(*i)++;
	if (line[*i] == '\0')
	{
		ft_printf(2, "minishell: syntax error: open quote not supported\n");
		return (-1);
	}
	if (line[*i] == '\"')
		(*i)++;
	return (0);
}

int	ft_word_end(char *line, int *i)
{
	while (line[*i] != '\0' && ft_strchr(" \t|><", line[*i]) == NULL)
	{
		if (line[*i] == '\'')
		{
			if (ft_single_quote(line, i) == -1)
				return (-1);
		}
		else if (line[*i] == '\"')
		{
			if (ft_double_quote(line, i) == -1)
				return (-1);
		}
		else if (line[*i] != '\0')
			(*i)++;
	}
	return (*i);
}
