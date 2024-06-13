/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:29:33 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/12 17:06:28 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_cmd	*ft_lstnew_c(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (new == NULL)
		return (NULL);
	new->path = NULL;
	new->path_hc = NULL;
	new->args = NULL;
	new->redir_in = NULL;
	new->redir_out = NULL;
	new->next = NULL;
	return (new);
}
