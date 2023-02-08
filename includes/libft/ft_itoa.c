/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:43:09 by mpelazza          #+#    #+#             */
/*   Updated: 2022/11/10 10:02:31 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrlen(long nbr)
{
	int	len;

	len = 1;
	if (nbr < 0)
	{
		++len;
		nbr = -nbr;
	}
	while (nbr > 9)
	{
		++len;
		nbr /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*nbr;
	long	ln;

	len = ft_nbrlen(n);
	nbr = malloc(sizeof(char) * (len + 1));
	if (!nbr)
		return (NULL);
	ln = (long)n;
	nbr[len--] = '\0';
	if (ln < 0)
	{
		nbr[0] = '-';
		ln = -ln;
	}
	while (ln > 9)
	{
		nbr[len--] = (ln % 10) + 48;
		ln /= 10;
	}
	nbr[len] = ln + 48;
	return (nbr);
}
