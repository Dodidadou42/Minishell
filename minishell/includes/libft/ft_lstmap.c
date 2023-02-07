/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:00:29 by mpelazza          #+#    #+#             */
/*   Updated: 2022/11/14 16:53:43 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*lst_map;

	if (!lst || !f)
		return (NULL);
	lst_map = ft_lstnew(f(lst->content));
	if (!lst_map)
		return (NULL);
	lst = lst->next;
	while (lst && lst->content)
	{
		new = ft_lstnew(f(lst->content));
		if (!new && del)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&lst_map, new);
		lst = lst->next;
	}
	return (lst_map);
}
