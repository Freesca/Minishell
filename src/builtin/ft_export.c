/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:01:22 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/14 15:31:01 by fdonati          ###   ########.fr       */
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

static void	ft_export_err(char *str)
{
	ft_printf(2, "minishell: export: `");
	ft_printf(2, str);
	ft_printf(2, "': not a valid identifier\n");
}

static int	ft_export_lexer(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
	{
		ft_export_err(str);
		return (1);
	}
	if (str[0] == '=')
	{
		ft_export_err(str);
		return (1);
	}
	while (str[i] != '\0' && str[i] != '=')
	{
		if (ft_isalpha(str[0]) == 0
			|| ft_isalnum(str[i]) == 0)
		{
			ft_export_err(str);
			return (1);
		}
		i++;
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
		if (ft_export_lexer(cmd->args[i]) == 1)
			return (1);
		ret = ft_export_value(cmd->args[i], envp);
		if (ret != 0)
			return (ret);
		i++;
	}
	return (0);
}
