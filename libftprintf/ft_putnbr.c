/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:07:02 by mzeggaf           #+#    #+#             */
/*   Updated: 2023/11/13 20:23:11 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_digits(int n)
{
	int	digits;

	digits = 1;
	while (n / 10)
	{
		digits *= 10;
		n /= 10;
	}
	return (digits);
}

int	ft_putnbr(int nbr)
{
	int	digits;
	int	sign;
	int	len;

	len = 0;
	sign = 1;
	if (nbr < 0)
	{
		sign = -1;
		len += ft_putchar('-');
	}
	digits = get_digits(nbr);
	while (digits)
	{
		len += ft_putchar(sign * (nbr / digits) + 48);
		nbr %= digits;
		digits /= 10;
	}
	return (len);
}
