/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:59:53 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/23 15:00:25 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	ft_print_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp != NULL)
	{
		ft_printf(1, "type: %d, str: %s\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
} */

int	ft_tokenize(char *line, t_token **token, t_env *envp)
{
	int		i;
	int		cmd_count;
	int		ret;

	*token = NULL;
	i = 0;
	cmd_count = 0;
	ret = 0;
	line = ft_swap_envp(line, envp);
	if (line == NULL)
		return (-1);
	while (line[i] != '\0')
	{
		if (ft_strchr(" \t", line[i]) != NULL)
			i++;
		else if (ft_strchr("|><", line[i]) != NULL)
			ret = ft_special_char(token, line, &i, &cmd_count);
		else
			ret = ft_word(token, line, &i, &cmd_count);
		if (ret != 0)
			return (ret);
	}
	ret = ft_lexer(token);
	/* ft_print_token(*token); */
	return (free(line), ret);
}
