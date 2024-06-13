/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:59:25 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/12 14:12:57 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_lexer_error3(t_token *tmp)
{
	ft_printf(2, "minishell: syntax error near");
	ft_printf(2, "unexpected token `%s'\n", tmp->next->value);
	return (2);
}

static int	ft_lexer_error2(t_token *tmp)
{
	if (tmp->next == NULL)
	{
		ft_printf(2, "minishell: syntax error near");
		ft_printf(2, "unexpected token `newline'\n");
	}
	else
	{
		ft_printf(2, "minishell: syntax error near");
		ft_printf(2, "unexpected token `%s'\n", tmp->next->value);
	}
	return (2);
}

static int	ft_lexer_error(t_token *tmp)
{
	ft_printf(2, "minishell: syntax error near");
	ft_printf(2, "unexpected token `%s'\n", tmp->value);
	return (2);
}

int	ft_lexer(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if (tmp == NULL)
		return (0);
	if (tmp->type == T_PIPE)
		return (ft_lexer_error(tmp));
	while (tmp != NULL)
	{
		if ((tmp->type == T_PIPE || tmp->type == T_REDIR_IN
				|| tmp->type == T_REDIR_OUT || tmp->type == T_REDIR_APPEND
				|| tmp->type == T_REDIR_HEREDOC)
			&& (tmp->next == NULL || tmp->next->type == T_PIPE))
			return (ft_lexer_error2(tmp));
		if ((tmp->type == T_REDIR_IN || tmp->type == T_REDIR_OUT
				|| tmp->type == T_REDIR_APPEND
				|| tmp->type == T_REDIR_HEREDOC)
			&& (tmp->next != NULL) && (tmp->next->type == T_REDIR_IN
				|| tmp->next->type == T_REDIR_OUT
				|| tmp->next->type == T_REDIR_APPEND
				|| tmp->next->type == T_REDIR_HEREDOC))
			return (ft_lexer_error3(tmp));
		tmp = tmp->next;
	}
	return (0);
}
