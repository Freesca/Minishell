/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:00:56 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/17 16:15:38 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

static void	ft_signal_handler_cmd(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf(1, "\n");
		g_exit_status = 130;
	}
	else if (signum == SIGQUIT)
	{
		ft_printf(1, "Quit: (core dumped)\n");
		g_exit_status = 131;
	}
}

static void	ft_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf(1, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130;
	}
	else if (signum == SIGQUIT)
	{
		ft_printf(1, "Quit: (core dumped)\n");
		g_exit_status = 131;
	}
}

static void	ft_readline(t_env **envp, int *exit_status,
						t_token **token)
{
	char	*line;

	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	line = readline("minishell$ ");
	*exit_status = 0;
	if (!line)
	{
		ft_printf(1, "exit\n");
		ft_free_n_exit(0, NULL, NULL, envp);
	}
	if (g_exit_status != 0)
	{
		*exit_status = ft_update_status(g_exit_status, envp);
		g_exit_status = 0;
	}
	add_history(line);
	*exit_status = ft_tokenize(line, token, *envp);
}

int	main(int argc, char **argv, char **environ)
{
	int		exit_status;
	t_env	*envp;
	t_token	*token;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	exit_status = 0;
	envp = ft_env_init(environ);
	if (envp == NULL)
		ft_free_n_err(-1, NULL, NULL, NULL);
	while (1)
	{
		ft_readline(&envp, &exit_status, &token);
		if (exit_status == 0)
		{
			signal(SIGQUIT, ft_signal_handler_cmd);
			signal(SIGINT, ft_signal_handler_cmd);
			exit_status = ft_command(&token, &cmd, &envp);
		}
		exit_status = ft_update_status(exit_status, &envp);
		ft_free_n_err(exit_status, &token, &cmd, &envp);
	}
	return (0);
}
