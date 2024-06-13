/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:25:43 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/11 16:36:58 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_parent(t_cmd *cmd, t_data *data, int cmd_count)
{
	if (cmd_count > 0)
		close(data->fd_in);
	if (cmd->next != NULL)
	{
		close(data->pipe_fd[1]);
		data->fd_in = data->pipe_fd[0];
	}
	else
	{
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
	}
}

static int	ft_wait_n_restore(pid_t pid, t_data *data, int cmd_count)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (i < cmd_count)
	{
		if (wait(&status) == pid)
		{
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				status = WTERMSIG(status) + 128;
			close(data->pipe_fd[0]);
			close(data->pipe_fd[1]);
			close(data->fd_in);
			dup2(data->original_stdin, STDIN_FILENO);
			dup2(data->original_stdout, STDOUT_FILENO);
			close(data->original_stdin);
			close(data->original_stdout);
		}
		i++;
	}
	return (status);
}

int	ft_exec(t_cmd **cmd, t_env **envp, t_data *data)
{
	pid_t	pid;
	int		status;
	int		cmd_count;

	status = 0;
	cmd_count = 0;
	if ((*cmd)->next == NULL)
	{
		if (ft_is_builtin(*cmd))
			return (ft_exec_builtin(cmd, envp, data, cmd_count));
	}
	while ((*cmd) != NULL && status == 0 && pipe(data->pipe_fd) != -1)
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
			ft_exec_child(cmd, envp, data, cmd_count);
		ft_parent(*cmd, data, cmd_count);
		cmd_count++;
		ft_lstcut_c(cmd);
	}
	status = ft_wait_n_restore(pid, data, cmd_count);
	return (status);
}
