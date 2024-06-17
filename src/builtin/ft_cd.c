/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:26:36 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/14 14:27:51 by fdonati          ###   ########.fr       */
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
		{
			ft_printf(2, "minishell: cd: HOME not set\n");
			return (1);
		}
	}
	else if (ft_strcmp(cmd->args[1], "-") == 0)
	{
		*path = ft_get_envp_value("OLDPWD", envp);
		if (*path == NULL)
		{
			ft_printf(2, "minishell: cd: OLDPWD not set\n");
			return (1);
		}
	}
	else
		*path = ft_strdup(cmd->args[1]);
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

static void	ft_update_value(t_env **envp, char *key, char *value)
{
	char	*str;
	t_env	*new;

	str = NULL;
	new = NULL;
	if (ft_change_value(*envp, key, value) == 0)
	{
		str = ft_strjoin(key, "=");
		if (str == NULL)
			return ;
		str = ft_strfjoin(str, value);
		if (str == NULL)
			return ;
		new = ft_lstnew_e(str, EXP_VAR);
		free(str);
		if (new == NULL)
			return ;
		ft_lstaddback_e(envp, new);
	}
}

int	ft_cd(t_cmd *cmd, t_env **envp)
{
	char	*path;
	char	*oldpwd;
	char	*pwd;

	path = NULL;
	oldpwd = NULL;
	pwd = NULL;
	if (ft_get_path(cmd, &path, *envp) != 0)
		return (1);
	oldpwd = ft_get_envp_value("PWD", *envp);
	if (chdir(path) == -1)
	{
		ft_free_cd(path, oldpwd, NULL);
		ft_printf(2, "minishell: cd: ");
		ft_printf(2, "%s: No such file or directory\n", cmd->args[1]);
		return (1);
	}
	if (ft_get_pwd(&pwd, oldpwd, path) != 0)
		return (1);
	ft_update_value(envp, "PWD", pwd);
	ft_update_value(envp, "OLDPWD", oldpwd);
	ft_free_cd(path, oldpwd, pwd);
	return (0);
}
