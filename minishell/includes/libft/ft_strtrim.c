/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:15:52 by mpelazza          #+#    #+#             */
/*   Updated: 2022/11/14 12:27:19 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isset(char c, const char *set)
{
	int	i;

	i = -1;
	while (set[++i])
		if (set[i] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s1_trim;
	int		start;
	int		len;

	if (!s1)
		return (NULL);
	start = 0;
	while (s1[start] && ft_isset(s1[start], set))
		++start;
	if (!s1[start])
		len = 1;
	else
	{
		len = ft_strlen(s1) - 1;
		while (ft_isset(s1[len], set))
			--len;
		len = (len - start) + 2;
	}
	s1_trim = malloc(sizeof(char) * len);
	if (!s1_trim)
		return (NULL);
	s1_trim[0] = 0;
	if (len > 0)
		ft_strlcpy(s1_trim, &s1[start], len);
	return (s1_trim);
}
