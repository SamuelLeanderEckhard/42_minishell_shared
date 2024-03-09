/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:17:03 by bszabo            #+#    #+#             */
/*   Updated: 2023/09/27 13:17:14 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// print a character to stdout and return the number of characters written
int	print_char(int c)
{
	char	c_c;

	c_c = (c);
	return (write(1, &c_c, 1));
}

// print the string to stdout and return the number of characters written
int	print_str(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (*str)
	{
		write(1, str, 1);
		str++;
		len++;
	}
	return (len);
}

// print integer to stdout and return the number of characters written
int	print_int(int n)
{
	int		count;
	char	c_num;

	count = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	else if (n < 0)
	{
		count += write(1, "-", 1);
		n *= -1;
	}
	if (n > 9)
	{
		count += print_int(n / 10);
		count += print_int(n % 10);
	}
	else
	{
		c_num = n + '0';
		count += write(1, &c_num, 1);
	}
	return (count);
}

// print unsigned integer to stdout and return the number of characters written
int	print_uint(unsigned int n)
{
	int		count;
	char	c_num;

	count = 0;
	c_num = n + '0';
	if (n < 10)
		count += write(1, &c_num, 1);
	else
	{
		count += print_uint(n / 10);
		count += print_uint(n % 10);
	}
	return (count);
}
