/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:17:25 by mpelazza          #+#    #+#             */
/*   Updated: 2022/11/08 17:05:37 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	nb;
	int		sign;

	i = 0;
	nb = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		++i;
	if (str[i] == '+')
		++i;
	else if (str[i] == '-')
	{
		sign = -sign;
		++i;
	}
	while (ft_isdigit(str[i]))
	{
		nb += str[i] - 48;
		if (ft_isdigit(str[++i]))
			nb *= 10;
	}
	return (nb * sign);
}
