/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:54:52 by tlivroze          #+#    #+#             */
/*   Updated: 2023/05/23 03:03:48 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	conv(char a)
{
	long	i;

	i = a - 48;
	return (i);
}

long	ft_atol(const char *nptr)
{
	long			result;
	long			n;

	result = 0;
	n = 1;
	while ((*nptr >= 9 && *nptr <= 15) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			n = -1;
		nptr++;
	}
	while (*nptr > 47 && *nptr < 58)
	{
		if (*nptr > 47 && *nptr < 58)
			result = (result * 10) + conv(*nptr);
		nptr++;
	}
	result = result * n;
	return (result);
}
