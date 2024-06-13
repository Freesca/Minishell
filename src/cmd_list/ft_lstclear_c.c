/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 16:47:42 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/12 20:00:54 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstunlink_c(char **path_hc)
{
	int		i;

	i = 0;
	if (path_hc == NULL || path_hc[i] == NULL)
		return ;
	while (path_hc[i] != NULL)
	{
		unlink(path_hc[i]);
		i++;
	}
}

void	ft_lstclear_c(t_cmd **lst)
{
	t_cmd	*tmp;

	if (lst == NULL || *lst == NULL)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		if ((*lst)->path != NULL)
			free((*lst)->path);
		if ((*lst)->path_hc != NULL)
		{
			ft_lstunlink_c((*lst)->path_hc);
			ft_free_mtx((*lst)->path_hc);
		}
		if ((*lst)->args != NULL)
			ft_free_mtx((*lst)->args);
		if ((*lst)->redir_in != NULL)
			free((*lst)->redir_in);
		if ((*lst)->redir_out != NULL)
			free((*lst)->redir_out);
		free(*lst);
		*lst = tmp;
	}
}
