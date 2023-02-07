/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:51:47 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/02 06:45:06 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcpy(t_list *lst)
{
	t_list	*copy;
	t_list	*tmp;

	copy = NULL;
	tmp = lst;
	while (tmp)
	{
		ft_lstadd_back(&copy, ft_lstnew(tmp->content));
		tmp = tmp->next;
	}
	return (copy);
}
