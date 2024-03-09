/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:42:37 by bszabo            #+#    #+#             */
/*   Updated: 2023/09/05 11:43:31 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// check if the character is printable
// return 1 if true, 0 if false
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	int c1 = ' ';
	int c2 = 'r';
	int c3 = '~';
	int c4 = '	';
	int res1 = ft_isprint(c1);
	int res2 = ft_isprint(c2);
	int res3 = ft_isprint(c3);
	int res4 = ft_isprint(c4);
	printf("%c | %d\n", c1, res1);
	printf("%c | %d\n", c2, res2);
	printf("%c | %d\n", c3, res3);
	printf("%c | %d\n", c4, res4);
	return (0);
}
*/
