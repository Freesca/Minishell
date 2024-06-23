/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:01:22 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/23 16:26:28 by fdonati          ###   ########.fr       */
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

static int	ft_plus_flag(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '+')
		i++;
	if (str[i] == '+')
		return (1);
	return (0);
}

static int	ft_export_value(char *str, t_env **envp)
{
	int		flag;
	char	*key;
	char	*value;
	t_env	*new;

	new = NULL;
	flag = ft_plus_flag(str);
	if (ft_key_n_value(str, &key, &value) == -1)
		return (-1);
	if (ft_change_value(envp, key, value, flag) != 1)
	{
		new = ft_lstnew_e(str, EXP_VAR);
		if (new == NULL)
		{
			free(key);
			free(value);
			return (1);
		}
		ft_lstaddback_e(envp, new);
	}
	free(key);
	free(value);
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
		if (ft_export_lexer(cmd->args[i]) == 1)
			return (1);
		ret = ft_export_value(cmd->args[i], envp);
		if (ret != 0)
			return (ret);
		i++;
	}
	return (0);
}
