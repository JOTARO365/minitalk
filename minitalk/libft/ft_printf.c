/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waon-in <waon-in@student.42>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 06:41:11 by waon-in           #+#    #+#             */
/*   Updated: 2024/03/22 00:19:46 by waon-in          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i] != '\0')
		i += ft_putchar(str[i]);
	return (i);
}

int	ft_check(va_list *args, char c)
{
	int	length;

	length = 0;
	if (c == 'c')
		length += ft_putchar(va_arg(*args, int));
	else if (c == 's')
		length += ft_putstr(va_arg(*args, char *));
	else if (c == 'p')
		length += ft_putnbr_p(va_arg(*args, unsigned long));
	else if (c == 'd' || c == 'i')
		length += ft_putnbr(va_arg(*args, int));
	else if (c == 'u')
		length += ft_putnbr_u(va_arg(*args, unsigned int));
	else if (c == 'x')
		length += ft_putnbr_x(va_arg(*args, unsigned int));
	else if (c == 'X')
		length += ft_putnbr_xb(va_arg(*args, unsigned int));
	else if (c == '%')
		length += ft_putchar('%');
	return (length);
}

int	ft_printf(const char *s, ...)
{
	va_list		args;
	int			length;
	int			i;

	length = 0;
	i = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			length += ft_check(&args, s[i]);
		}
		else
			length += ft_putchar(s[i]);
		i++;
	}
	return (length);
}
