/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_mtx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:02:04 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/06 15:04:15 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_visible_env_vars(t_env *envp)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = envp;
	while (tmp != NULL)
	{
		if (tmp->type != HDN_VAR)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

static char	*ft_create_env_string(t_env *env_var)
{
	char	*env_str;

	env_str = ft_strdup(env_var->key);
	if (env_str == NULL)
		return (NULL);
	if (env_var->value != NULL)
	{
		env_str = ft_strfjoin(env_str, "=");
		if (env_str == NULL)
			return (NULL);
		env_str = ft_strfjoin(env_str, env_var->value);
		if (env_str == NULL)
			return (NULL);
	}
	return (env_str);
}

static char	**ft_convert_env_list_to_matrix(t_env *envp, int count)
{
	t_env	*tmp;
	char	**mtx;
	int		i;

	i = 0;
	tmp = envp;
	mtx = malloc(sizeof(char *) * (count + 1));
	if (mtx == NULL)
		return (NULL);
	while (tmp != NULL)
	{
		if (tmp->type != HDN_VAR)
		{
			mtx[i] = ft_create_env_string(tmp);
			if (mtx[i] == NULL)
			{
				ft_free_mtx(mtx);
				return (NULL);
			}
			i++;
		}
		tmp = tmp->next;
	}
	mtx[i] = NULL;
	return (mtx);
}

char	**ft_env_to_mtx(t_env *envp)
{
	int	count;

	count = ft_count_visible_env_vars(envp);
	return (ft_convert_env_list_to_matrix(envp, count));
}

/* char	**ft_env_to_mtx(t_env *envp)
{
	char	**mtx;
	t_env	*tmp;
	int		i;

	tmp = envp;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->type != HDN_VAR)
			i++;
		tmp = tmp->next;
	}
	mtx = malloc(sizeof(char *) * (i + 1));
	if (mtx == NULL)
		return (NULL);
	i = 0;
	tmp = envp;
	while (tmp != NULL)
	{
		if (tmp->type != HDN_VAR)
		{
			mtx[i] = ft_strdup(tmp->key);
			if (mtx[i] == NULL)
			{
				ft_free_mtx(mtx);
				return (NULL);
			}
			mtx[i] = ft_strfjoin(mtx[i], "=");
			if (mtx[i] == NULL)
			{
				ft_free_mtx(mtx);
				return (NULL);
			}
			mtx[i] = ft_strfjoin(mtx[i], tmp->value);
			if (mtx[i] == NULL)
			{
				ft_free_mtx(mtx);
				return (NULL);
			}
			i++;
		}
		tmp = tmp->next;
	}
	mtx[i] = NULL;
	return (mtx);
} */
