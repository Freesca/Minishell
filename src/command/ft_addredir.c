/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addredir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:18:36 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/12 18:15:31 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_addredir(t_token_type type, char *value, int **redir)
{
	if (*redir != NULL)
		free(*redir);
	*redir = malloc(sizeof(int));
	if (*redir == NULL)
		return (-1);
	if (type == T_REDIR_OUT)
		**redir = open(value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (type == T_REDIR_APPEND)
		**redir = open(value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (type == T_REDIR_IN || type == T_REDIR_HEREDOC)
		**redir = open(value, O_RDONLY);
	if (**redir < 0)
	{
		ft_printf(2, "minishell: %s: No such file or directory\n", value);
		return (0);
	}
	return (0);
}
