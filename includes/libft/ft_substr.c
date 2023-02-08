/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 09:16:51 by mpelazza          #+#    #+#             */
/*   Updated: 2022/11/14 12:24:26 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	long	sub_len;
	char	*sub_s;

	if (!s)
		return (NULL);
	sub_len = ft_strlen(s) - start;
	if (sub_len <= 0)
		sub_len = 0;
	else if ((unsigned int)sub_len > len)
		sub_len = (int)len;
	sub_s = malloc(sizeof(char) * (sub_len + 1));
	if (!sub_s)
		return (NULL);
	if (!sub_len)
		sub_s[0] = '\0';
	else
		ft_strlcpy(sub_s, &s[start], sub_len + 1);
	return (sub_s);
}
