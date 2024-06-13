/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:51:37 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/12 14:31:49 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(t_cmd *cmd)
{
	if (cmd->args == NULL)
		return (0);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (1);
	return (0);
}

int	ft_exec_builtin(t_cmd **cmd, t_env **envp, t_data *data, int cmd_count)
{
	int	ret;

	ret = 0;
	signal(SIGPIPE, SIG_IGN);
	if (ft_strcmp((*cmd)->args[0], "echo") == 0)
		ret = ft_echo(*cmd);
	if (ft_strcmp((*cmd)->args[0], "exit") == 0)
		return (ft_exit(cmd, envp, cmd_count));
	if (ft_strcmp((*cmd)->args[0], "export") == 0)
		return (ft_export(*cmd, envp));
	if (ft_strcmp((*cmd)->args[0], "unset") == 0)
		return (ft_unset(*cmd, envp));
	if (ft_strcmp((*cmd)->args[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp((*cmd)->args[0], "cd") == 0)
		return (ft_cd(*cmd, *envp));
	if (ft_strcmp((*cmd)->args[0], "env") == 0)
		return (ft_env(*envp));
	dup2(data->original_stdin, STDIN_FILENO);
	dup2(data->original_stdout, STDOUT_FILENO);
	close(data->original_stdin);
	close(data->original_stdout);
	return (ret);
}
