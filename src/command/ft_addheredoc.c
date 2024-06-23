/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addheredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:06:57 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/20 14:08:29 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_signal_handler_hc(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf(1, "\n");
		close(STDIN_FILENO);
		g_exit_status = 130;
	}
	if (signum == SIGQUIT)
		ft_printf(1, "\b\b  \b\b");
}

static int	ft_open_hc(char **str)
{
	int		fd;

	fd = -1;
	*str = ft_strdup(".tmp_heredoc");
	while (fd < 0)
	{
		*str = ft_strfjoin(*str, "1");
		fd = open(*str, O_WRONLY | O_CREAT | O_EXCL, 0644);
	}
	return (fd);
}

static int	ft_line_hc(int fd, char *lim, int quote, t_env *envp)
{
	char	*line;

	ft_printf(1, "> ");
	line = ft_get_next_line(0);
	if (line == NULL || ((ft_strncmp(line, lim, ft_strlen(lim)) == 0
				&& line[ft_strlen(lim)] == '\n')))
	{
		if (line == NULL && g_exit_status == 0)
		{
			ft_printf(2, "minishell: warning: here-document ");
			ft_printf(2, "delimited by end-of-file (wanted `%s')\n", lim);
		}
		free(line);
		return (-1);
	}
	if (quote == 1)
		line = ft_swap_envp_hc(line, envp);
	ft_printf(fd, "%s", line);
	free(line);
	return (0);
}

int	ft_addheredoc(char **lim_to_strhc, char ***path_hc, int quote, t_env *envp)
{
	char	*strhc;
	int		fd;

	signal(SIGINT, ft_signal_handler_hc);
	signal(SIGQUIT, ft_signal_handler_hc);
	strhc = NULL;
	fd = ft_open_hc(&strhc);
	ft_addarg(strhc, path_hc);
	while (1)
	{
		if (ft_line_hc(fd, *lim_to_strhc, quote, envp) == -1)
			break ;
	}
	close(fd);
	free(*lim_to_strhc);
	*lim_to_strhc = strhc;
	if (g_exit_status == 130)
		return (-1);
	return (0);
}
