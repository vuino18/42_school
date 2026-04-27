/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:35:32 by elino             #+#    #+#             */
/*   Updated: 2025/07/17 13:45:09 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putptr_rec(uintptr_t n)
{
	int		counter;
	char	*base;

	counter = 0;
	base = "0123456789abcdef";
	if (n >= 16)
		counter += ft_putptr_rec(n / 16);
	counter += ft_putchar(base[n % 16]);
	return (counter);
}

int	ft_putptr(uintptr_t n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		return (ft_putstr("(nil)"));
	counter += ft_putstr("0x");
	counter += ft_putptr_rec(n);
	return (counter);
}
