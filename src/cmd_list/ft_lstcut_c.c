/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcut_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:27:03 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/12 19:57:23 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstcut_c(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (*cmd == NULL)
		return ;
	tmp = *cmd;
	*cmd = (*cmd)->next;
	free(tmp->path);
	ft_lstunlink_c(tmp->path_hc);
	ft_free_mtx(tmp->path_hc);
	ft_free_mtx(tmp->args);
	free(tmp->redir_in);
	free(tmp->redir_out);
	free(tmp);
}
