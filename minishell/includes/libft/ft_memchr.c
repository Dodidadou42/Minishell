/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:44:28 by mpelazza          #+#    #+#             */
/*   Updated: 2022/11/10 12:52:09 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*s_bis;

	i = -1;
	s_bis = (unsigned char *)s;
	while (++i < n)
		if (s_bis[i] == (unsigned char)c)
			return ((void *)&s[i]);
	return (NULL);
}
