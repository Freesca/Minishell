/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:08:38 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/18 13:30:33 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sign(int c)
{
	if (c == '+')
		return (1);
	return (-1);
}

static size_t	ft_get_sign(const char c, size_t *z, int *error)
{
	if (*error != 0)
		return (0);
	if (c == '-' || c == '+')
	{
		*z = *z + 1;
		return (ft_sign(c));
	}
	return (1);
}

static intmax_t	ft_mount_num(const char *nptr, int *error)
{
	intmax_t	i;
	size_t		z;
	size_t		sign;
	intmax_t	num;

	i = 0;
	z = 0;
	sign = 1;
	num = 0;
	while (ft_isspace(nptr[z]))
		z++;
	if (nptr[z] == '\0')
		*error = 1;
	sign = ft_get_sign(nptr[z], &z, error);
	while (*error == 0 && (nptr[z] && nptr[z] >= '0' && nptr[z] <= '9'))
	{
		num = i;
		i = i * 10 + nptr[z] - '0';
		if (num > i)
			*error = 1;
		z++;
	}
	return (i * sign);
}

long long	ft_atoll_err(const char *nptr, int *error)
{
	intmax_t	num;

	*error = 0;
	num = ft_mount_num(nptr, error);
	if (*error == 1)
		return (0);
	if (num < LLONG_MIN || num > LLONG_MAX)
	{
		*error = 1;
		return (0);
	}
	return ((long long)num);
}
