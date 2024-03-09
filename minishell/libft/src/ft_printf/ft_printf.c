/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:38:36 by bszabo            #+#    #+#             */
/*   Updated: 2023/09/27 10:44:16 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// check character after '%', if it is a valid specifier, handle it
// if it is not a valid specifier, just return without doing anything
// return the number of characters printed
static int	handle_percent(const char **str, va_list arg_ptr)
{
	int	count;

	count = 0;
	(*str)++;
	if (**str == '\0')
		return (0);
	else if (**str == 'c')
		count += print_char(va_arg(arg_ptr, int));
	else if (**str == 's')
		count += print_str(va_arg(arg_ptr, char *));
	else if (**str == 'p')
		count += print_ptr(va_arg(arg_ptr, void *));
	else if (**str == 'd' || **str == 'i')
		count += print_int(va_arg(arg_ptr, int));
	else if (**str == 'u')
		count += print_uint(va_arg(arg_ptr, int));
	else if (**str == 'x' || **str == 'X')
		count += print_hex(va_arg(arg_ptr, unsigned int), **str);
	else if (**str == '%')
		count += write(1, "%", 1);
	return (count);
}

// check characters in 'str', if not '%' then print it, otherwise handle it
// return the number of characters printed
int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	arg_ptr;

	count = 0;
	va_start(arg_ptr, str);
	if (*str == 0)
		return (-1);
	while (*str)
	{
		if (*str != '%')
			count += write(1, str, 1);
		else if (*str == '%')
			count += handle_percent(&str, arg_ptr);
		str++;
	}
	va_end(arg_ptr);
	return (count);
}
