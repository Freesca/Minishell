/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:26:36 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/07 22:39:07 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_cd(char *path, char *oldpwd, char *pwd)
{
	if (path != NULL)
		free(path);
	if (oldpwd != NULL)
		free(oldpwd);
	if (pwd != NULL)
		free(pwd);
}

static int	ft_get_path(t_cmd *cmd, char **path, t_env *envp)
{
	*path = NULL;
	if (cmd->args[1] == NULL)
	{
		*path = ft_get_envp_value("HOME", envp);
		if (*path == NULL)
			return (1);
	}
	else if (ft_strcmp(cmd->args[1], "-") == 0)
	{
		*path = ft_get_envp_value("OLDPWD", envp);
		if (*path == NULL)
			return (1);
	}
	else
		*path = ft_strdup(cmd->args[1]);
	return (0);
}

static int	ft_get_oldpwd(char **oldpwd, char *path)
{
	*oldpwd = getcwd(NULL, 0);
	if (*oldpwd == NULL)
	{
		ft_free_cd(path, NULL, NULL);
		return (1);
	}
	return (0);
}

static int	ft_get_pwd(char **pwd, char *oldpwd, char *path)
{
	*pwd = getcwd(NULL, 0);
	if (*pwd == NULL)
	{
		ft_free_cd(path, oldpwd, NULL);
		return (1);
	}
	return (0);
}

int	ft_cd(t_cmd *cmd, t_env *envp)
{
	char	*path;
	char	*oldpwd;
	char	*pwd;

	path = NULL;
	oldpwd = NULL;
	pwd = NULL;
	if (ft_get_path(cmd, &path, envp) != 0)
		return (1);
	if (ft_get_oldpwd(&oldpwd, path) != 0)
		return (1);
	if (chdir(path) == -1)
	{
		ft_free_cd(path, oldpwd, NULL);
		ft_printf(2, "minishell: cd: ");
		ft_printf(2, "%s: No such file or directory\n", cmd->args[1]);
		return (1);
	}
	if (ft_get_pwd(&pwd, oldpwd, path) != 0)
		return (1);
	ft_change_value(envp, "PWD", pwd);
	ft_change_value(envp, "OLDPWD", oldpwd);
	ft_free_cd(path, oldpwd, pwd);
	return (0);
}
