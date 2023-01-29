/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:06:42 by ddychus           #+#    #+#             */
/*   Updated: 2022/11/15 15:30:44 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (!ft_strlen(little))
		return ((char *)big);
	if (!big && len == 0)
		return (0);
	while (big[i] && i < len)
	{
		if (big[i] == *little)
		{
			j = 1;
			while (big[j + i] == little[j] && little[j])
				j++;
			if (i + j > len)
				return (0);
			if (!little[j])
				return ((char *)&big[i]);
		}
		i++;
	}
	return (0);
}
