/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 22:46:28 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/07 22:47:10 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	while (tmp != NULL)
	{
		if (tmp->type == ENV_VAR)
			ft_printf(1, "%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
