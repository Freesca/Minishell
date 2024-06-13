/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback_e.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:35:37 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/07 23:10:38 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstaddback_e(t_env **list, t_env *new)
{
	t_env	*tmp;

	tmp = NULL;
	if (!list || !new)
		return ;
	if (!(*list))
	{
		*list = new;
		(*list)->next = NULL;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
}
