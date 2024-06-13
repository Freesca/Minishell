/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 22:08:59 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/06 15:06:13 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long long	ft_isatoll(char *str, int *err)
{
	int			i;
	long long	nmb;

	i = 0;
	nmb = 0;
	if (str[i] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
		{
			ft_printf(2, "its not a number\n");
			return (-1);
		}
		i++;
	}
	nmb = ft_atoll_err(str, err);
	if (*err != 0)
		return (-1);
	nmb = nmb % 256;
	if (nmb < 0)
		nmb = 256 + nmb;
	return (nmb);
}

int	ft_exit(t_cmd **cmd, t_env **envp, int cmd_count)
{
	long long	exit;
	int			err;

	exit = 0;
	err = 0;
	if (cmd_count == 0 && (*cmd)->next == NULL)
		ft_printf(2, "exit\n");
	if ((*cmd)->args[1] != NULL)
	{
		exit = ft_isatoll((*cmd)->args[1], &err);
		if (err != 0)
		{
			ft_printf(2, "minishell: exit: ");
			ft_printf(2, "%s: numeric argument required\n", (*cmd)->args[1]);
			ft_free_n_exit(2, NULL, cmd, envp);
		}
		if ((*cmd)->args[2] != NULL)
		{
			ft_printf(2, "minishell: exit: too many arguments\n");
			return (1);
		}
	}
	ft_free_n_exit((int) exit, NULL, cmd, envp);
	return (0);
}
