/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:54:14 by elino             #+#    #+#             */
/*   Updated: 2025/07/14 15:04:57 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putuint(unsigned int n)
{
	int	counter;

	counter = 0;
	if (n > 9)
		counter += ft_putuint(n / 10);
	counter += ft_putchar((n % 10) + '0');
	return (counter);
}
