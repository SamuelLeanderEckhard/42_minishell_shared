/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:16:22 by bszabo            #+#    #+#             */
/*   Updated: 2023/09/13 16:30:45 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// create a new node with the content ’content’
t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
/*
#include <stdio.h>
int	main(void)
{
	int num = 42;
	char *str = "hello world";
	t_list *new_node = ft_lstnew(str);
	t_list *new_node2 = ft_lstnew(&num);
	printf("new node content: %s\n", (char *)new_node->content);
	printf("new node2 content: %d\n", *(int *)new_node2->content);
	free(new_node);
	free(new_node2);
	return (0);
}
*/
