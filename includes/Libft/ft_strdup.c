/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:11:38 by ddychus           #+#    #+#             */
/*   Updated: 2022/11/17 16:08:18 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *source)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(source) + 1));
	if (!str)
		return (0);
	while (source[i])
	{
		str[i] = source[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
