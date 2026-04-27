/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:06:18 by elino             #+#    #+#             */
/*   Updated: 2025/07/17 13:45:42 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

int	ft_printf(const char *str, ...);
int	ft_putstr(char *s);
int	ft_putnbr(int n);
int	ft_putchar(int c);
int	ft_puthex(unsigned int n, char format);
int	ft_putpct(void);
int	ft_putptr(uintptr_t n);
int	ft_putuint(unsigned int n);

#endif
