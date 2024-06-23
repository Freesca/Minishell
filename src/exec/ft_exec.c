/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:25:43 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/21 18:13:06 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_restore(t_data *data)
{
	close(data->pipe_fd[1]);
	close(data->pipe_fd[0]);
	dup2(data->original_stdin, STDIN_FILENO);
	dup2(data->original_stdout, STDOUT_FILENO);
	close(data->original_stdin);
	close(data->original_stdout);
}

static int	ft_wait_n_restore(pid_t pid, t_data *data, int cmd_count)
{
	int		i;
	int		status;
	int		tmp_status;
	pid_t	wait_pid;

	status = 0;
	tmp_status = 0;
	i = 0;
	while (i < cmd_count)
	{
		wait_pid = wait(&tmp_status);
		if (pid == wait_pid)
		{
			status = tmp_status;
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				status = WTERMSIG(status) + 128;
			ft_restore(data);
		}
		i++;
	}
	return (status);
}

int	ft_exec(t_cmd **cmd, t_env **envp, t_data *data)
{
	int		status;
	int		cmd_count;
	pid_t	pid;
	pid_t	last_pid;

	status = 0;
	cmd_count = 0;
	if ((*cmd)->next == NULL && ft_is_builtin(*cmd) == 1)
		return (ft_exec_builtin_solo(cmd, envp, data, cmd_count));
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
		if ((*cmd)->next == NULL)
			last_pid = pid;
		ft_lstcut_c(cmd);
	}
	return (ft_wait_n_restore(pid, data, cmd_count));
}
