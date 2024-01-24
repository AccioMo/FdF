/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:33:18 by mzeggaf           #+#    #+#             */
/*   Updated: 2023/11/13 18:13:05 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned long	get_hexdigits(unsigned long n)
{
	unsigned long	digits;

	digits = 1;
	while (n / 16)
	{
		digits *= 16;
		n /= 16;
	}
	return (digits);
}

int	ft_puthex(unsigned int nbr, const char *base)
{
	unsigned int	digits;
	int				len;

	len = 0;
	digits = get_hexdigits(nbr);
	while (digits)
	{
		len += ft_putchar(base[nbr / digits]);
		nbr %= digits;
		digits /= 16;
	}
	return (len);
}

int	ft_putaddr(unsigned long addr)
{
	unsigned long	digits;
	int				len;

	len = ft_putstr("0x");
	digits = get_hexdigits(addr);
	while (digits)
	{
		len += ft_putchar(LOWER_HEX[addr / digits]);
		addr %= digits;
		digits /= 16;
	}
	return (len);
}
