/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:11:49 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/14 11:17:15 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*ft_token_to_pipe(t_token *token)
{
	while (token != NULL && token->type != T_PIPE)
		token = token->next;
	if (token != NULL)
		token = token->next;
	return (token);
}

int	ft_args_init(t_cmd *cmd, t_token *token, t_env **envp)
{
	while (token != NULL && token->type != T_PIPE)
	{
		if (token->type == T_COMMAND)
		{
			if (ft_addpath(token->value, &cmd->path, envp) < 0)
				return (-1);
			if (ft_addarg(token->value, &cmd->args) != 0)
				return (-1);
		}
		if (token->type == T_WORD)
		{
			if (ft_addarg(token->value, &cmd->args) != 0)
				return (-1);
		}
		token = token->next;
	}
	return (0);
}

int	ft_hc_init(t_cmd *cmd, t_token *token, t_env **envp)
{
	int	ret;

	ret = 0;
	while (token != NULL && token->type != T_PIPE && ret >= 0)
	{
		if (token->type == T_REDIR_HEREDOC)
		{
			if (token->next->type == T_LIM_QUOTE)
				ret = ft_addheredoc(&token->next->value,
						&cmd->path_hc, 2, *envp);
			else
				ret = ft_addheredoc(&token->next->value,
						&cmd->path_hc, 1, *envp);
		}
		token = token->next;
	}
	return (ret);
}

int	ft_redir_init(t_cmd *cmd, t_token *token, t_env **envp)
{
	int	ret;

	(void)envp;
	ret = 0;
	while (token != NULL && token->type != T_PIPE && ret >= 0)
	{
		if (token->type == T_REDIR_IN || token->type == T_REDIR_HEREDOC)
			ret = ft_addredir(token->type, token->next->value,
					&cmd->redir_in);
		if (token->type == T_REDIR_OUT || token->type == T_REDIR_APPEND)
			ret = ft_addredir(token->type, token->next->value,
					&cmd->redir_out);
		if (ret != 0)
			return (0);
		token = token->next;
	}
	return (ret);
}

int	ft_command_fill(t_cmd *cmd, t_token *token, t_env **env,
							int (*f)(t_cmd *, t_token *, t_env **))
{
	t_cmd	*cmd_tmp;
	t_token	*token_tmp;
	int		ret;

	ret = 0;
	cmd_tmp = cmd;
	token_tmp = token;
	while (cmd_tmp != NULL && ret >= 0)
	{
		ret = f(cmd_tmp, token_tmp, env);
		cmd_tmp = cmd_tmp->next;
		token_tmp = ft_token_to_pipe(token_tmp);
	}
	return (ret);
}
