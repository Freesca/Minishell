/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_special_char.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:51:43 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/11 23:22:49 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*ft_pipe_char(void)
{
	t_token	*new;
	char	*str;

	str = strdup("|");
	new = ft_lstnew_t(T_PIPE, str);
	if (new == NULL)
		return (NULL);
	return (new);
}

static t_token	*ft_redirect_out_char(int *i, char *line)
{
	t_token	*new;
	char	*str;

	str = strdup(">");
	new = ft_lstnew_t(T_REDIR_OUT, str);
	if (new == NULL)
		return (NULL);
	if (line[*i + 1] == '>')
	{
		new->type = T_REDIR_APPEND;
		free(str);
		str = strdup(">>");
		new->value = str;
		(*i)++;
	}
	return (new);
}

static t_token	*ft_redir_in_char(int *i, char *line)
{
	t_token	*new;
	char	*str;

	str = strdup("<");
	new = ft_lstnew_t(T_REDIR_IN, str);
	if (new == NULL)
		return (NULL);
	if (line[*i + 1] == '<')
	{
		new->type = T_REDIR_HEREDOC;
		free(str);
		str = strdup("<<");
		new->value = str;
		(*i)++;
	}
	return (new);
}

int	ft_special_char(t_token **token, char *line, int *i, int *cmd_count)
{
	t_token	*new;

	new = NULL;
	if (line[*i] == '|')
	{
		new = ft_pipe_char();
		*cmd_count = 0;
	}
	else if (line[*i] == '>')
		new = ft_redirect_out_char(i, line);
	else if (line[*i] == '<')
		new = ft_redir_in_char(i, line);
	if (new == NULL)
		return (-1);
	ft_lstadd_back_t(token, new);
	(*i)++;
	return (0);
}
