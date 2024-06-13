/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_e.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:00:06 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/06 10:01:30 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear_e(t_env **list)
{
	t_env	*tmp;

	if (!list)
		return ;
	while (*list != NULL)
	{
		tmp = (*list)->next;
		if ((*list)->key != NULL)
			free((*list)->key);
		if ((*list)->value != NULL)
			free((*list)->value);
		free(*list);
		*list = tmp;
	}
}
