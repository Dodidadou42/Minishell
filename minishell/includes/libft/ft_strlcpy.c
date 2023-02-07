/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 08:28:10 by mpelazza          #+#    #+#             */
/*   Updated: 2022/11/10 14:52:23 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int		i;

	i = -1;
	if (!dstsize)
		return ((size_t)ft_strlen(src));
	while (src[++i] && --dstsize)
		dst[i] = src[i];
	dst[i] = '\0';
	return ((size_t)ft_strlen(src));
}
