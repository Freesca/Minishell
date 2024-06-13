/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:08:07 by fdonati           #+#    #+#             */
/*   Updated: 2023/10/27 15:25:24 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	number;

	sign = 1;
	number = 0;
	while (*nptr != '\0')
	{
		while ((*nptr == ' ') || (*nptr == '\t') || (*nptr == '\n')
			|| (*nptr == '\v') || (*nptr == '\f') || (*nptr == '\r'))
			nptr++;
		if (*nptr == '-' || *nptr == '+')
		{
			if (*nptr == '-')
				sign = -1;
			nptr++;
		}
		while (*nptr >= '0' && *nptr <= '9')
		{
			number = (number * 10) + ((int) *nptr - '0');
			nptr++;
		}
		return (number * sign);
	}
	return (0);
}

/*
int	main()
{
	char *str = "   - 1234";
	printf("%d\n", ft_atoi(str));
	printf("%-5.4d", 333);
	return (0);
}
*/