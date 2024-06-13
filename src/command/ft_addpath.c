/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 16:38:28 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/10 14:24:35 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_split_path(t_env **envp)
{
	char	*path_value;
	char	**path_split;
	t_env	*tmp;

	tmp = *envp;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
		{
			path_value = ft_strdup(tmp->value);
			if (path_value == NULL)
				return (NULL);
			path_split = ft_split(path_value, ':');
			free(path_value);
			return (path_split);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static int	ft_addpath_n_access(char **path_split,
								char **path, const char *value)
{
	int	i;

	if (path_split == NULL)
		return (-1);
	i = 0;
	while (path_split[i] != NULL)
	{
		*path = ft_strjoin(path_split[i], "/");
		if (*path == NULL)
			return (12);
		*path = ft_strfjoin(*path, value);
		if (*path == NULL)
			return (12);
		if (access(*path, F_OK) == 0)
		{
			ft_free_mtx(path_split);
			return (0);
		}
		free(*path);
		i++;
	}
	*path = NULL;
	ft_free_mtx(path_split);
	return (1);
}

int	ft_addpath(char *value, char **path, t_env **envp)
{
	char	**path_split;
	int		ret;

	if (value == NULL || value[0] == '\0')
		return (0);
	path_split = ft_split_path(envp);
	if (path_split == NULL)
		return (-1);
	ret = ft_addpath_n_access(path_split, path, value);
	return (ret);
}
