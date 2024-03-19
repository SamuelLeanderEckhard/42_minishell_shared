/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:01:15 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/19 20:41:43 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// find next occurrence of 'quote' in 'line' starting at index 'i'
// return index of next 'quote' or index of null terminator
int	find_next_quote(char *line, int i, char quote)
{
	i++;
	while (line[i] && line[i] != quote)
		i++;
	return (i);
}

// count number of substrings in string 'str' separated by char 'c'
// return number of substrings
static int	count_substrs(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] != c && str[i])
			{
				if (str[i] == S_QUOTE)
					i = find_next_quote(str, i, S_QUOTE);
				else if (str[i] == D_QUOTE)
					i = find_next_quote(str, i, D_QUOTE);
				i++;
			}
		}
		else
			i++;
	}
	return (count);
}

// count number of characters in substring starting at index 'i'
static int	get_substr_len(char *str, char c, int i)
{
	int	count;

	count = 0;
	while (str[i] != c && str[i])
	{
		if (str[i] == S_QUOTE)
		{
			count += find_next_quote(str, i, S_QUOTE) - i;
			i += find_next_quote(str, i, S_QUOTE) - i;
		}
		else if (str[i] == D_QUOTE)
		{
			count += find_next_quote(str, i, D_QUOTE) - i;
			i += find_next_quote(str, i, D_QUOTE) - i;
		}
		count++;
		i++;
	}
	return (count);
}

// fill 'arr' array with substrings
// return 0 if successful, -1 if malloc fails
int	fill_arr(char **arr, char *str, char c)
{
	int	i;
	int	str_index;
	int	substr_len;

	i = 0;
	str_index = 0;
	substr_len = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		substr_len = get_substr_len(str, c, i);
		if (substr_len > 0)
		{
			arr[str_index] = malloc(sizeof(char) * (substr_len + 1));
			if (arr[str_index] == NULL)
				return (ft_free_str_arr(arr), -1);
			ft_strlcpy(arr[str_index], &str[i], substr_len + 1);
			str_index++;
		}
		i += substr_len;
	}
	return (0);
}

// split string 'str' into substrings using char 'c' as delimiter
// same as ft_split, but if 'c' is inside single or double quotes, it is ignored
// return array of substrings with NULL ending if successful, NULL if fails
char	**ft_split_quotes(char *str, char c)
{
	int		substrs;
	char	**arr;

	if (str == NULL)
		return (NULL);
	substrs = count_substrs(str, c);
	arr = (char **)malloc((substrs + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	arr[substrs] = NULL;
	if (substrs == 0)
		return (arr);
	if (fill_arr(arr, str, c) == -1)
		return (NULL);
	return (arr);
}

/*
#include <stdio.h>
int main(void)
{
	// char *str = " <>   split    'this   ' by  space!  <>  ";
	char *str = "echo 'hello | world' | ls -l | grep c | wc -l";
	// char *str = "";
	char **res_arr = ft_split_quotes(str, '|');
	if (res_arr == NULL)
	{
		printf("ft_split_quotes() returned NULL\n");
		return (1);
	}

	printf("str: %s\n", str);
	int i = 0;
	while (res_arr[i])
	{
		printf("res_arr[%d] %s\n", i, res_arr[i]);
		if (res_arr[++i] == NULL)
			printf("res_arr[%d] NULL\n", i);
	}

	for (int i = 0; res_arr[i]; i++)
		free(res_arr[i]);
	free(res_arr);
	return (0);
}
*/
