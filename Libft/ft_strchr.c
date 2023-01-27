/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:44:27 by ddychus           #+#    #+#             */
/*   Updated: 2022/12/13 15:49:10 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchr(const char *str, int searchedChar)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)searchedChar)
			return (i);
		i++;
	}
	return (0);
}
