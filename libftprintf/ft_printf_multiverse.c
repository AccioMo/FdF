/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_multiverse.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:32:32 by mzeggaf           #+#    #+#             */
/*   Updated: 2023/11/18 15:27:23 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_multiverse(char flag, va_list args)
{
	if (flag == '%')
		return (ft_putchar('%'));
	else if (flag == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (flag == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (flag == 'd' || flag == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (flag == 'u')
		return (ft_putunbr(va_arg(args, unsigned int)));
	else if (flag == 'p')
		return (ft_putaddr(va_arg(args, unsigned long)));
	else if (flag == 'x')
		return (ft_puthex(va_arg(args, unsigned int), LOWER_HEX));
	else if (flag == 'X')
		return (ft_puthex(va_arg(args, unsigned int), UPPER_HEX));
	return (0);
}
