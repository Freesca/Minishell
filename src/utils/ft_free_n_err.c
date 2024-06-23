/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_n_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:37:43 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/23 17:20:29 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_mtx(char **mtx)
{
	int	i;

	i = 0;
	if (mtx == NULL)
		return ;
	while (mtx[i] != NULL)
	{
		free(mtx[i]);
		i++;
	}
	if (mtx != NULL)
		free(mtx);
}

static void	ft_close_fd(void)
{
	int	i;

	i = 3;
	while (i < 1024)
	{
		close(i);
		i++;
	}
}

void	ft_free_n_exit(int err, t_token **token, t_cmd **cmd, t_env **envp)
{
	ft_close_fd();
	rl_clear_history();
	if (token != NULL)
	{
		ft_lstclear_t(token);
		*token = NULL;
	}
	if (cmd != NULL)
	{
		ft_lstclear_c(cmd);
		*cmd = NULL;
	}
	if (envp != NULL)
	{
		ft_lstclear_e(envp);
		*envp = NULL;
	}
	exit(err);
}

void	ft_free_n_err(int err, t_token **token, t_cmd **cmd, t_env **envp)
{
	ft_close_fd();
	if (token != NULL)
	{
		ft_lstclear_t(token);
		*token = NULL;
	}
	if (cmd != NULL)
	{
		ft_lstclear_c(cmd);
		*cmd = NULL;
	}
	else if (err < 0)
	{
		if (envp != NULL)
		{
			ft_lstclear_e(envp);
			*envp = NULL;
		}
		strerror(errno);
		exit(errno);
	}
}
