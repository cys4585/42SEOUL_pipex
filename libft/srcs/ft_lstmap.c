/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:49:09 by youngcho          #+#    #+#             */
/*   Updated: 2022/04/10 16:53:01 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	lstclear_nodes(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*node;

	if (lst == NULL || f == NULL)
		return (NULL);
	head = ft_lstnew(f(lst->content));
	if (head == NULL)
		return (NULL);
	node = head;
	while (lst->next)
	{
		node->next = ft_lstnew(f(lst->next->content));
		if (node->next == NULL)
		{
			if (del)
				ft_lstclear(&head, del);
			else
				lstclear_nodes(head);
			return (NULL);
		}
		node = node->next;
		lst = lst->next;
	}
	return (head);
}
