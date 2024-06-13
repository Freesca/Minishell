/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:01:22 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/06 15:06:34 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_export(t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	while (tmp != NULL)
	{
		if (tmp->type != HDN_VAR)
		{
			ft_printf(1, "declare -x ");
			ft_printf(1, tmp->key);
			if (tmp->value != NULL)
			{
				ft_printf(1, "=\"");
				ft_printf(1, tmp->value);
				ft_printf(1, "\"");
			}
			ft_printf(1, "\n");
		}
		tmp = tmp->next;
	}

}

static int	ft_export_value(char *str, t_env **envp)
{
	t_env	*new;
	char	*key;
	char	*value;
	int		ret;

	new = NULL;
	ret = ft_key_n_value(str, &key, &value);
	if (ret == -1)
		return (-1);
	if (ft_change_value(*envp, key, value) == 1)
	{
		free(key);
		free(value);
		return (0);
	}
	else
	{
		new = ft_lstnew_e(str, EXP_VAR);
		free(key);
		free(value);
		if (!new)
			return (-1);
		ft_lstaddback_e(envp, new);
	}
	return (0);
}

int	ft_export(t_cmd *cmd, t_env **envp)
{
	int		i;
	int		ret;

	i = 1;
	if (cmd->args[1] == NULL)
	{
		ft_print_export(*envp);
		return (0);
	}
	while (cmd->args[i] != NULL)
	{
		if (ft_isalpha(cmd->args[i][0]) == 0)
		{
			ft_printf(2, "minishell: export: `");
			ft_printf(2, cmd->args[i]);
			ft_printf(2, "': not a valid identifier\n");
			return (1);
		}
		ret = ft_export_value(cmd->args[i], envp);
		if (ret != 0)
			return (ret);
		i++;
	}
	return (0);
}
