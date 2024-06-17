/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:03:42 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/17 16:04:01 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe(t_cmd *cmd, t_data *data, int *cmd_count, int pid)
{
	if (cmd->next != NULL && pid == 0)
	{
		close(data->pipe_fd[0]);
		dup2(data->pipe_fd[1], STDOUT_FILENO);
		close(data->pipe_fd[1]);
	}
	if (cmd->next == NULL && pid == 0)
	{
		dup2(data->original_stdout, STDOUT_FILENO);
		close(data->original_stdout);
	}
	if (cmd->next != NULL && pid != 0)
	{
		close(data->pipe_fd[1]);
		dup2(data->pipe_fd[0], STDIN_FILENO);
		close(data->pipe_fd[0]);
	}
	if (pid != 0)
		(*cmd_count)++;
}
