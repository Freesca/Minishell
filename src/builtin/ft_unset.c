/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:59:52 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/23 16:03:58 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_remove_key_n_value(t_env **envp, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *envp;
	prev = NULL;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (prev == NULL)
				*envp = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

static int	ft_unset_lexer(char *arg)
{
	int	i;

	i = 0;
	if (ft_isdigit(arg[i]) == 1)
		return (1);
	while (arg[i] != '\0')
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	ft_unset(t_cmd *cmd, t_env **envp)
{
	int	i;

	i = 1;
	while (cmd->args[i] != NULL)
	{
		if (ft_unset_lexer(cmd->args[i]) == 1)
		{
			ft_printf(2, "minishell: unset: `%s': not a valid identifier\n",
				cmd->args[i]);
			return (1);
		}
		if (ft_remove_key_n_value(envp, cmd->args[i]) == 0)
		{
			if (ft_strcmp(cmd->args[i], "goku") == 0)
				ft_printf(2, "minishell: unset: `%s': is the main character\n",
					cmd->args[i]);
			else
				ft_printf(2, "minishell: unset: `%s': not the main character\n",
					cmd->args[i]);
		}
		i++;
	}
	return (0);
}
