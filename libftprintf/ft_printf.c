/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:23:59 by mzeggaf           #+#    #+#             */
/*   Updated: 2023/11/18 15:39:30 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_strchr(const char *str, int c)
{
	while (*str && *str != (char)c)
		str++;
	if (!(*str) && (char)c != '\0')
		return (NULL);
	return ((char *)str);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	va_list	args;

	len = 0;
	if (write(1, "", 0) == -1)
		return (-1);
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			len += ft_printf_multiverse(*str, args);
			if (*str && ft_strchr("cspdiuxX%", (int)*str))
				str++;
		}
		else
			len += write(1, str++, 1);
	}
	va_end(args);
	return (len);
}
