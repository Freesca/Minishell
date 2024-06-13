/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:59:01 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/07 16:22:32 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_printf(2, "minishell: pwd: error: cannot ");
		ft_printf(2, "find current directory: No such file or directory\n");
		return (1);
	}
	ft_printf(1, "%s\n", pwd);
	free(pwd);
	return (0);
}
