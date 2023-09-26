/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_bool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:11:07 by tlivroze          #+#    #+#             */
/*   Updated: 2023/09/23 05:59:21 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	ft_atoi_bool(char *str, int	*nb)
{
	char	*str2;

	if (!str)
		return (false);
	str2 = ft_itoa(ft_atoi(str));
	if (ft_strncmp(str, str2, ft_strlen(str)))
	{
		free(str2);
		return (false);
	}
	*nb = ft_atoi(str);
	free(str2);
	return (true);
}
