/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:31:08 by mzeggaf           #+#    #+#             */
/*   Updated: 2023/11/13 20:21:47 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_digits(unsigned int n)
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

int	ft_putunbr(unsigned int nbr)
{
	int	digits;
	int	len;

	len = 0;
	digits = get_digits(nbr);
	while (digits)
	{
		len += ft_putchar((nbr / digits) + 48);
		nbr %= digits;
		digits /= 10;
	}
	return (len);
}
