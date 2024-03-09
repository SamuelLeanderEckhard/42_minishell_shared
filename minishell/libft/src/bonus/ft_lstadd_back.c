/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:51:42 by bszabo            #+#    #+#             */
/*   Updated: 2023/09/14 17:49:24 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// add the node ’new’ at the end of the list
// if the list is empty, the new node is the beginning of the list
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	last_node = ft_lstlast(*lst);
	if (last_node == NULL)
	{
		*lst = new;
		return ;
	}
	last_node->next = new;
}
/*
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	char *str1 = "hello";
	char *str2 = "world";
	char *str_new = "!!!";
	t_list *node1 = ft_lstnew(str1);
	t_list *node2 = ft_lstnew(str2);
	t_list *new_node = ft_lstnew(str_new);
	t_list *root = node1;
	node1->next = node2;
	t_list *ptr = root;

	while (ptr)
	{
		printf("%s | ", (char *)ptr->content);
		ptr = ptr->next;
	}
	printf("\n");
	ptr = root;
	ft_lstadd_back(&root, new_node);
	while (ptr)
    {
        printf("%s | ", (char *)ptr->content);
        ptr = ptr->next;
    }

	free(node1);
	free(node2);
	free(new_node);
	return (0);
}
*/
