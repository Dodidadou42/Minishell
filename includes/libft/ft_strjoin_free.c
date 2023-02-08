/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 03:21:17 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/07 19:42:41 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, int n_free)
{
	int		len;
	char	*s_join;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	s_join = malloc(sizeof(char) * len);
	if (s_join)
	{
		ft_strlcpy(s_join, s1, len);
		ft_strlcat(s_join, s2, len);
	}
	if (n_free == 1 || n_free > 2)
		free(s1);
	if (n_free == 2 || n_free > 2)
		free(s2);
	return (s_join);
}
