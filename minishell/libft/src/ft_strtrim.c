/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 10:53:21 by bszabo            #+#    #+#             */
/*   Updated: 2023/09/10 10:56:16 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// return 1 if 'c' is in 'set', 0 otherwise
static int	is_in_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

// calculate the start index and the length of the trimmed string
static void	calc_trim(int *start, int *cpylen, char const *s1, char const *set)
{
	int	strlen;
	int	i;

	strlen = (int)ft_strlen(s1);
	i = 0;
	while (is_in_set(s1[i], set))
		i++;
	if (i == strlen)
	{
		*start = 0;
		*cpylen = 0;
		return ;
	}
	*start = i;
	i = 0;
	while (is_in_set(s1[strlen - i - 1], set))
		i++;
	*cpylen = (strlen - i) - *start;
}

// remove 'set' characters from the beginning and the end of 's1'
// return a copy of the trimmed string using malloc
char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		cpylen;
	char	*cpy;
	int		i;

	start = 0;
	cpylen = 0;
	i = 0;
	calc_trim(&start, &cpylen, s1, set);
	cpy = (char *)malloc((cpylen + 1) * sizeof(char));
	if (cpy == NULL)
		return (NULL);
	while (i < cpylen)
	{
		cpy[i] = s1[start + i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
/*
#include <stdio.h>
int main(void)
{
	char *str = "-  ++ ---hello world!- -+-+- -";
	// char *str = "   xxx   xxx";
	char *set = "- +";
	// char *set = " x";
	char *res = ft_strtrim(str, set);
	printf("str: |%s|\ntrim: |%s|\nresult: |%s|\n", str, set, res);
	free(res);
	return (0);
}
*/