/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:25:43 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/17 16:03:56 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (data->fd_in != STDIN_FILENO)
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
			return (ft_exec_builtin_solo(cmd, envp, data, cmd_count));
	}
	while ((*cmd) != NULL)
	{
		if ((*cmd)->next != NULL)
			pipe(data->pipe_fd);
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
			ft_exec_child(cmd, envp, data, cmd_count);
		ft_pipe(*cmd, data, &cmd_count, pid);
		ft_lstcut_c(cmd);
	}
	status = ft_wait_n_restore(pid, data, cmd_count);
	return (status);
}
