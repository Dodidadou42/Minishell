/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:27:02 by mpelazza          #+#    #+#             */
/*   Updated: 2022/11/11 08:59:46 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s_mapi;
	int		i;

	if (!s)
		return (NULL);
	s_mapi = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!s_mapi)
		return (NULL);
	i = -1;
	while (s[++i])
		s_mapi[i] = f(i, s[i]);
	s_mapi[i] = '\0';
	return (s_mapi);
}
