/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:59:26 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/18 11:30:37 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_export_err(char *str)
{
	ft_printf(2, "minishell: export: `");
	ft_printf(2, str);
	ft_printf(2, "': not a valid identifier\n");
}

int	ft_export_lexer(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0' || str[0] == '=')
	{
		ft_export_err(str);
		return (1);
	}
	while (str[i] != '\0' && str[i] != '=')
	{
		if ((ft_isalpha(str[0]) == 0 && str[0] != '_')
			|| (ft_isalnum(str[i]) == 0
				&& str[i] != '+' && str[i] != '_'))
		{
			ft_export_err(str);
			return (1);
		}
		if (str[i] == '+' && str[i + 1] != '=')
		{
			ft_export_err(str);
			return (1);
		}
		i++;
	}
	return (0);
}
