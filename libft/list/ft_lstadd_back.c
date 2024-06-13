/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:07:21 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/07 23:11:42 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

/*Parameters
	lst: The address of a pointer to the first link of
	a list.
	new: The address of a pointer to the node to be
	added to the list.
Return value
	None
External functs
	None
Description
	Adds the node ’new’ at the end of the list.*/