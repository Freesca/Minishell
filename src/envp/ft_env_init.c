/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:33:18 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/14 13:19:21 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_env_init(char **envp)
{
	t_env	*env;
	t_env	*new;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i] != NULL)
	{
		new = ft_lstnew_e(envp[i], ENV_VAR);
		if (new == NULL)
		{
			ft_lstclear_e(&env);
			return (NULL);
		}
		ft_lstaddback_e(&env, new);
		i++;
	}
	new = ft_lstnew_e("?=0", HDN_VAR);
	if (new == NULL)
	{
		ft_lstclear_e(&env);
		return (NULL);
	}
	ft_lstaddback_e(&env, new);
	return (env);
}
