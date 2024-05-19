/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:05:19 by bszabo            #+#    #+#             */
/*   Updated: 2023/09/14 15:23:02 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// count the number of nodes in a linked list
int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
/*
#include <stdio.h>
#include <stdlib.h>
int	main(void)
{
	char *str1 = "hello";
	char *str2 = "world";
	t_list *node1 = ft_lstnew(str1);
	t_list *node2 = ft_lstnew(str2);
	t_list *root = node1;
	node1->next = node2;
	int size = ft_lstsize(root);
	printf("size: %d\n", size);
	free(node1);
	free(node2);
	return (0);
}
*/
