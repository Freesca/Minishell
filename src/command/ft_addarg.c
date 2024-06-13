/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addarg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:13:38 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/10 14:13:47 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	ft_addarg(char *value, char ***args)
{
	char	**new;
	int		i;

	i = 0;
	while ((*args) != NULL && (*args)[i] != NULL)
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (new == NULL)
		return (-1);
	i = 0;
	while ((*args) != NULL && (*args)[i] != NULL)
	{
		new[i] = (*args)[i];
		i++;
	}
	new[i] = ft_strdup(value);
	if (new[i] == NULL)
	{
		ft_free_mtx(new);
		return (-1);
	}
	new[i + 1] = NULL;
	free(*args);
	*args = new;
	return (0);
}


