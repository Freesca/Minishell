/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:52:01 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/13 11:41:29 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_was_redir(t_token_type type)
{

	if (type == T_REDIR_IN || type == T_REDIR_APPEND
		|| type == T_REDIR_HEREDOC || type == T_REDIR_OUT)
		return (1);
	return (0);
}

static t_token	*ft_fd_token(char *str, t_token **token)
{
	t_token	*new;

	if (ft_lstlast_t(*token)->type == T_REDIR_HEREDOC)
	{
		if (*str == '\'' || *str == '\"')
			new = ft_lstnew_t(T_LIM_QUOTE, str);
		else
			new = ft_lstnew_t(T_LIM, str);
	}
	else
		new = ft_lstnew_t(T_FD, str);
	if (new == NULL)
		return (NULL);
	return (new);
}

static t_token	*ft_word_token(char *str, int *cmd_count)
{
	t_token			*new;
	t_token_type	type;

	if (*cmd_count == 0)
	{
		type = T_COMMAND;
		*cmd_count = 1;
	}
	else
		type = T_WORD;
	new = ft_lstnew_t(type, str);
	if (new == NULL)
	{
		free(str);
		return (NULL);
	}
	return (new);
}

static int	ft_new_token(t_token **new, t_token **token,
				char *str, int *cmd_count)
{
	if (*token != NULL && (ft_was_redir((ft_lstlast_t(*token))->type)) == 1)
		*new = ft_fd_token(str, token);
	else
		*new = ft_word_token(str, cmd_count);
	if (*new == NULL)
	{
		free(str);
		return (-1);
	}
	return (0);
}

int	ft_word(t_token **token, char *line, int *i, int *cmd_count)
{
	int		start;
	int		end;
	char	*str;
	t_token	*new;

	start = *i;
	new = NULL;
	end = ft_word_end(line, i);
	if (end == -1)
		return (2);
	str = ft_substr(line, start, end - start);
	if (str == NULL)
		return (-1);
	if (ft_new_token(&new, token, str, cmd_count) == -1)
		return (-1);
	/* if (*token != NULL && (ft_was_redir((ft_lstlast_t(*token))->type)) == 1)
		new = ft_fd_token(str, token);
	else
		new = ft_word_token(str, cmd_count);
	if (new == NULL)
	{
		free(str);
		return (-1);
	} */
	new->value = ft_quote_clean(str);
	if (new->value == NULL)
		return (-1);
	ft_lstadd_back_t(token, new);
	return (0);
}
