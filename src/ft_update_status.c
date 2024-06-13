/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:31:13 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/06 13:11:29 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_update_status(int status, t_env **envp)
{
	char	*value;

	value = ft_itoa(status);
	if (!value)
		return (-1);
	if (ft_change_value(*envp, "?", value) == -1)
	{
		free(value);
		return (-1);
	}
	free(value);
	return (0);
}
