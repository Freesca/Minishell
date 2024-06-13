/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_t.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:37:10 by fdonati           #+#    #+#             */
/*   Updated: 2024/04/18 17:44:25 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear_t(t_token **list)
{
	t_token	*tmp;

	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp->value);
		free(tmp);
	}
	*list = NULL;
	list = NULL;
}
