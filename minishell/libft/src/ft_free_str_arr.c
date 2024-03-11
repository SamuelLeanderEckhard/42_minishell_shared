/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:45:45 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/11 10:08:11 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// free all strings in the array and the array itself
void	ft_free_str_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}