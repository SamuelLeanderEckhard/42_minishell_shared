/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:37:30 by bszabo            #+#    #+#             */
/*   Updated: 2023/09/14 15:34:38 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// add the node ’new’ at the beginning of the list
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
/*
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	char *str1 = "hello";
	char *str2 = "world";
	char *str_new = "hi";
	t_list *node1 = ft_lstnew(str1);
	t_list *node2 = ft_lstnew(str2);
	t_list *new_node = ft_lstnew(str_new);
	t_list *root = node1;
	node1->next = node2;
	t_list *ptr = root;

	printf("first node value: %s\n", (char *)root->content);
	ft_lstadd_front(&ptr, new_node);
	root = ptr;
	printf("first node value: %s\n", (char *)root->content);
	free(node1);
	free(node2);
	free(new_node);
	return (0);
}
*/
