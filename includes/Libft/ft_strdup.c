/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:29:53 by mpelazza          #+#    #+#             */
/*   Updated: 2022/11/10 09:58:34 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s1_dup;
	int		i;

	s1_dup = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!s1_dup)
		return (NULL);
	i = -1;
	while (s1[++i])
		s1_dup[i] = s1[i];
	s1_dup[i] = '\0';
	return (s1_dup);
}
