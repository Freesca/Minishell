/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:21:23 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/14 13:05:37 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_bad_redir(t_cmd *cmd)
{
	if (cmd->redir_in != NULL && *cmd->redir_in == -1)
		return (1);
	if (cmd->redir_out != NULL && *cmd->redir_out == -1)
		return (1);
	return (0);
}

int	ft_redir(t_cmd **cmd)
{
	if (ft_bad_redir(*cmd) == 1)
		return (1);
	if ((*cmd)->redir_in != NULL && *(*cmd)->redir_in != -1)
		dup2(*(*cmd)->redir_in, STDIN_FILENO);
	if ((*cmd)->redir_out != NULL && *(*cmd)->redir_out != -1)
		dup2(*(*cmd)->redir_out, STDOUT_FILENO);
	return (0);
}
