/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:48:41 by mpelazza          #+#    #+#             */
/*   Updated: 2022/11/10 12:46:55 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dst_bis;
	char	*src_bis;

	if (!dst && !src)
		return (dst);
	dst_bis = (char *)dst;
	src_bis = (char *)src;
	while (n-- > 0)
		*dst_bis++ = *src_bis++;
	return (dst);
}
