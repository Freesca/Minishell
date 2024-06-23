/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 22:46:28 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/23 16:40:33 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_cmd *cmd, t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	if (cmd->args != NULL && cmd->args[1] != NULL)
	{
		ft_printf(2, "env: ’%s’: No such file or directory\n", cmd->args[1]);
		return (127);
	}
	while (tmp != NULL)
	{
		if (tmp->value != NULL && tmp->type != HDN_VAR)
			ft_printf(1, "%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
