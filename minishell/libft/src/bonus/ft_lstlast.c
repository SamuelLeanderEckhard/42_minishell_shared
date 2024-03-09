/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:23:29 by bszabo            #+#    #+#             */
/*   Updated: 2023/09/14 16:35:06 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// return the last element of the list
t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
/*
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	char *str1 = "hello";
	char *str2 = "world";
	t_list *node1 = ft_lstnew(str1);
	t_list *node2 = ft_lstnew(str2);
	t_list *root = NULL;
	node1->next = node2;
	t_list *last_node = ft_lstlast(root);
	printf("last node's content: %s\n", (char *)last_node->content);
	free(node1);
	free(node2);
	return (0);
}
*/
