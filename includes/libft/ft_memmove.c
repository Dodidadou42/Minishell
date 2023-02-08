/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:37:30 by mpelazza          #+#    #+#             */
/*   Updated: 2022/11/10 12:52:30 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_bis;
	char	*src_bis;
	size_t	i;

	if (!dst && !src)
		return (dst);
	dst_bis = (char *)dst;
	src_bis = (char *)src;
	i = -1;
	if (dst > src)
		while (len-- > 0)
			dst_bis[len] = src_bis[len];
	else
		while (++i < len)
			dst_bis[i] = src_bis[i];
	return (dst);
}
