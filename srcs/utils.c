/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:55:26 by tlivroze          #+#    #+#             */
/*   Updated: 2023/09/19 20:09:16 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

size_t	gettime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
