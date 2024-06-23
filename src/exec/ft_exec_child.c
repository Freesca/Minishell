/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:20:32 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/21 17:30:42 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_stat(char *path, t_cmd **cmd, t_env **envp)
{
	struct stat	buf;

	if (stat(path, &buf) < 0)
	{
		if (errno == ENOENT)
		{
			ft_printf(2, "minishell: %s: No such file or directory\n", path);
			ft_free_n_exit(127, NULL, cmd, envp);
		}
	}
	else if (S_ISDIR(buf.st_mode))
	{
		ft_printf(2, "minishell: %s: Is a directory\n", path);
		ft_free_n_exit(126, NULL, cmd, envp);
	}
	if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
	{
		ft_printf(2, "minishell: %s: Permission denied\n", path);
		ft_free_n_exit(126, NULL, cmd, envp);
	}
	ft_printf(2, "minishell: %s: Not a directory\n", path);
	ft_free_n_exit(126, NULL, cmd, envp);
}

static void	ft_path_dir(t_cmd **cmd, t_env **envp)
{
	if ((*cmd)->path == NULL)
	{
		if ((*cmd)->args == NULL || (*cmd)->args[0] == NULL)
			ft_free_n_exit(0, NULL, cmd, envp);
		if ((*cmd)->args != NULL && (*cmd)->args[0] != NULL)
		{
			if (ft_strchr((*cmd)->args[0], '/') != NULL)
				ft_stat((*cmd)->args[0], cmd, envp);
		}
		ft_printf(2, "minishell: %s: command not found\n", (*cmd)->args[0]);
		ft_free_n_exit(127, NULL, cmd, envp);
	}
}


void	ft_exec_child(t_cmd **cmd, t_env **envp,
						t_data *data, int cmd_count)
{
	int		bin_ret;
	char	**envp_cpy;

	bin_ret = 0;
	envp_cpy = NULL;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ft_pipe(*cmd, data, &cmd_count, 0);
	if (ft_redir(cmd) != 0)
		ft_free_n_exit(1, NULL, cmd, envp);
	if (ft_is_builtin(*cmd) == 1)
	{
		bin_ret = ft_exec_builtin(cmd, envp, data, cmd_count);
		ft_free_n_exit(bin_ret, NULL, cmd, envp);
	}
	ft_path_dir(cmd, envp);
	envp_cpy = ft_env_to_mtx(*envp);
	if (envp_cpy == NULL)
		ft_free_n_exit(errno, NULL, cmd, envp);
	execve((*cmd)->path, (*cmd)->args, envp_cpy);
	ft_free_mtx(envp_cpy);
	ft_free_n_exit(errno, NULL, cmd, envp);
}
