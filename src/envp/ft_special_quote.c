/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:17:04 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/23 14:50:34 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_toquote(char c)
{
	char	*quoted;

	quoted = NULL;
	if (c == '|')
		quoted = ft_strdup("\"|\"");
	else if (c == '<')
		quoted = ft_strdup("\"<\"");
	else if (c == '>')
		quoted = ft_strdup("\">\"");
	else if (c == '\'')
		quoted = ft_strdup("\"\'\"");
	else if (c == '\"')
		quoted = ft_strdup("\'\"\'");
	return (quoted);
}

static char	*ft_dtoquote(char *c)
{
	char	*quoted;

	quoted = NULL;
	if (ft_strncmp(c, ">>", 2) == 0)
		quoted = ft_strdup("\">>\"");
	else if (ft_strncmp(c, "<<", 2) == 0)
		quoted = ft_strdup("\"<<\"");
	return (quoted);
}

static char	*ft_char_quote(char *str, int *i, char c)
{
	char	*new_str;
	char	*quoted;

	quoted = ft_toquote(c);
	if (quoted == NULL)
		return (NULL);
	new_str = ft_strunion(str, quoted, *i, *i);
	if (new_str == NULL)
		return (NULL);
	free(str);
	free(quoted);
	*i += 2;
	return (new_str);
}

static char	*ft_dchar_quote(char *str, int *i, char *c)
{
	char	*new_str;
	char	*quoted;

	quoted = ft_dtoquote(c);
	if (quoted == NULL)
		return (NULL);
	new_str = ft_strunion(str, quoted, *i, *i);
	if (new_str == NULL)
		return (NULL);
	free(str);
	free(quoted);
	*i += 3;
	return (new_str);
}

char	*ft_special_quote(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = NULL;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (ft_strncmp(str + i, ">>", 2) == 0)
			str = ft_dchar_quote(str, &i, ">>");
		else if (ft_strncmp(str + i, "<<", 2) == 0)
			str = ft_dchar_quote(str, &i, "<<");
		else if (str[i] == '|' || str[i] == '<' || str[i] == '>'
			|| str[i] == '\'' || str[i] == '\"')
			str = ft_char_quote(str, &i, str[i]);
		i++;
	}
	return (str);
}
