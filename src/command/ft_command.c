/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:17:49 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/25 18:25:20 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_data_init(t_data *data)
{
	data->original_stdout = dup(STDOUT_FILENO);
	if (data->original_stdout == -1)
		return (-1);
	data->original_stdin = dup(STDIN_FILENO);
	if (data->original_stdin == -1)
		return (-1);
	return (0);
}

int	ft_command(t_token **token, t_cmd **cmd, t_env **envp)
{
	int		ret;
	t_data	data;

	ret = 0;
	data = (t_data){0};
	ret = ft_data_init(&data);
	if (ret == 0)
		ret = ft_command_init(cmd, *token, envp);
	dup2(data.original_stdin, STDIN_FILENO);
	if (ret == -2)
		return (1);
	if ((*cmd) == NULL || ((*cmd)->args == NULL && (*cmd)->next == NULL))
		return (ret);
	if (token != NULL)
	{
		ft_lstclear_t(token);
		*token = NULL;
	}
	if (ret >= 0)
		ret = ft_exec(cmd, envp, &data);
	return (ret);
}

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