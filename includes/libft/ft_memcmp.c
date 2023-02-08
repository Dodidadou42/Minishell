/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:29:45 by mpelazza          #+#    #+#             */
/*   Updated: 2022/11/14 09:54:43 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*s1_bis;
	unsigned char	*s2_bis;

	if (!n)
		return (0);
	i = 0;
	s1_bis = (unsigned char *)s1;
	s2_bis = (unsigned char *)s2;
	while (i + 1 < n && s1_bis[i] == s2_bis[i])
		++i;
	return ((unsigned char)s1_bis[i] - (unsigned char)s2_bis[i]);
}
