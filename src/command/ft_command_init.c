/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:22:18 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/12 19:02:35 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_cmd_init(t_cmd **cmd, t_token *token)
{
	t_cmd	*new;

	new = ft_lstnew_c();
	if (new == NULL)
		return (-1);
	ft_lstadd_back_c(cmd, new);
	while (token != NULL)
	{
		if (token->type == T_PIPE)
		{
			new = ft_lstnew_c();
			if (new == NULL)
			{
				free(new);
				return (-1);
			}
			ft_lstadd_back_c(cmd, new);
		}
		token = token->next;
	}
	return (0);
}

int	ft_command_init(t_cmd **cmd, t_token *token, t_env **env)
{
	int		ret;

	*cmd = NULL;
	ret = 0;
	if (token == NULL)
		return (0);
	ret = ft_cmd_init(cmd, token);
	if (ret == 0)
		ret = ft_command_fill(*cmd, token, env, ft_args_init);
	if (ret == 0)
		ret = ft_command_fill(*cmd, token, env, ft_hc_init);
	if (ret == 0)
		ret = ft_command_fill(*cmd, token, env, ft_redir_init);
	return (ret);
}
