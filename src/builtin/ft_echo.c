/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:10:23 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/03 15:37:09 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_n_flag(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
	{
		i++;
		while (arg[i] != '\0')
		{
			if (arg[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (cmd->args[i] != NULL)
	{
		if (n_flag != 2 && n_flag != -1 && ft_n_flag(cmd->args[i]) == 0)
			n_flag = 1;
		else
		{
			ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
			if (cmd->args[i + 1] != NULL)
				ft_putchar_fd(' ', STDOUT_FILENO);
			if (n_flag == 1)
				n_flag = 2;
			if (n_flag == 0)
				n_flag = -1;
		}
		i++;
	}
	if (n_flag <= 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
