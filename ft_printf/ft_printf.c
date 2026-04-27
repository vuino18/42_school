/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:09:59 by elino             #+#    #+#             */
/*   Updated: 2025/08/29 12:50:22 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_formats(va_list args, const char format)
{
	int	counter;

	counter = 0;
	if (format == 'c')
		counter += ft_putchar(va_arg(args, int));
	else if (format == 's')
		counter += ft_putstr(va_arg(args, char *));
	else if (format == 'p')
		counter += ft_putptr((uintptr_t)va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		counter += ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		counter += ft_putuint(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		counter += ft_puthex(va_arg(args, unsigned int), format);
	else if (format == '%')
		counter += ft_putpct();
	return (counter);
}

static int	handle_format(const char *str, va_list args)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1])
			{
				counter += ft_formats(args, str[i + 1]);
				i += 2;
			}
			else
				return (-1);
		}
		else
		{
			counter += ft_putchar(str[i]);
			i++;
		}
	}
	return (counter);
}

int	ft_printf(const char *str, ...)
{
	int		counter;
	va_list	args;

	va_start(args, str);
	counter = handle_format(str, args);
	va_end(args);
	return (counter);
}
