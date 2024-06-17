/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:17:49 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/17 14:30:09 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	ft_print_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	while (tmp)
	{
		ft_printf(1, "path: %s\n", tmp->path);
		i = 0;
		while (tmp->args != NULL && tmp->args[i])
		{
			ft_printf(1, "args[%d]: %s\n", i, tmp->args[i]);
			i++;
		}
		i = 0;
		while (tmp->path_hc != NULL && tmp->path_hc[i])
		{
			ft_printf(1, "path_hc[%d]: %s\n", i, tmp->path_hc[i]);
			i++;
		}
		if (tmp->redir_in)
			ft_printf(1, "redir_in: %d\n", *tmp->redir_in);
		if (tmp->redir_out)
			ft_printf(1, "redir_out: %d\n", *tmp->redir_out);
		tmp = tmp->next;
	}
} */

static int	ft_data_init(t_data *data)
{
	data->original_stdout = dup(STDOUT_FILENO);
	if (data->original_stdout == -1)
		return (-1);
	data->original_stdin = dup(STDIN_FILENO);
	if (data->original_stdin == -1)
		return (-1);
	data->fd_in = STDIN_FILENO;
	return (0);
}

/* static void	ft_print_mtx(char ***envp)
{
	int	i;

	i = 0;
	while ((*envp)[i] != NULL)
	{
		ft_printf(1, "%s\n", (*envp)[i]);
		i++;
	}
} */

int	ft_command(t_token **token, t_cmd **cmd, t_env **envp)
{
	int		ret;
	t_data	data;

	ret = 0;
	data = (t_data){0};
	ret = ft_data_init(&data);
	if (ret == 0)
		ret = ft_command_init(cmd, *token, envp);
	if (*cmd == NULL)
		return (ret);
	if ((*cmd)->args == NULL && (*cmd)->next == NULL)
		return (1);
	dup2(data.original_stdin, STDIN_FILENO);
	if (token != NULL)
	{
		ft_lstclear_t(token);
		*token = NULL;
	}
	/* ft_print_cmd(*cmd); */
	if (ret >= 0)
		ret = ft_exec(cmd, envp, &data);
	if (ret == -1)
		ret = 1;
	return (ret);
}
