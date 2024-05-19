/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 15:59:34 by bszabo            #+#    #+#             */
/*   Updated: 2023/09/15 16:31:47 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// iterate the list ’lst’ and apply the function ’f’ to the content of each node
// return a new list containing the new content values
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	void	*new_content;
	t_list	*new_node;

	new_lst = NULL;
	if (lst && f && del)
	{
		while (lst)
		{
			new_content = f(lst->content);
			new_node = ft_lstnew(new_content);
			if (new_node == NULL)
			{
				del(new_content);
				ft_lstclear(&new_lst, del);
				return (NULL);
			}
			ft_lstadd_back(&new_lst, new_node);
			lst = lst->next;
		}
	}
	return (new_lst);
}
