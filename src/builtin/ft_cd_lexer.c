/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:28:42 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/20 19:31:12 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_lexer(t_cmd *cmd)
{
	if (cmd->args != NULL && cmd->args[1] != NULL && cmd->args[2] != NULL)
	{
		ft_printf(2, "minishell: cd: too many arguments\n");
		return (1);
	}
	return (0);
}
