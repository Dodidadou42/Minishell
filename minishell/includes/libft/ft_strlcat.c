/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 08:59:43 by mpelazza          #+#    #+#             */
/*   Updated: 2022/11/10 13:46:05 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;

	if (!dstsize)
		return ((size_t)ft_strlen(src));
	i = 0;
	while (dst[i] && i < dstsize)
		++i;
	j = -1;
	while (src[++j] && dstsize && j + i < dstsize - 1)
		dst[i + j] = src[j];
	if (dstsize && i < dstsize)
		dst[i + j] = '\0';
	return ((size_t)(ft_strlen(src) + i));
}
