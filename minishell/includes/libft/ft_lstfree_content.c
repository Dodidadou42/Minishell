/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 01:57:13 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/02 06:45:20 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstfree_content(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		free(tmp->content);
		tmp = tmp->next;
	}
	while (*lst)
	{
		free(*lst);
		*lst = (*lst)->next;
	}
}
