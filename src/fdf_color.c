/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:09:55 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/19 15:19:19 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_atoi_hex(char *hex)
{
	unsigned int	nbr;
	int				digit;

	nbr = 0;
	hex += 2;
	while (*hex && *hex != '\n')
	{
		digit = ft_index(*hex, UPPER_HEX);
		if (digit == -1)
			digit = ft_index(*hex, LOWER_HEX);
		nbr = (nbr * 16) + digit;
		hex++;
	}
	return (nbr);
}

int	ft_intrapolate(int r0, int r1, float t)
{
	return (r0 + (r1 - r0) * t);
}

static void	ft_swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
}

int	ft_color(int ca, int cb, t_vector *v, float t)
{
	int	r;
	int	g;
	int	b;

	if (!v->rev)
		ft_swap(&ca, &cb);
	r = ft_intrapolate((ca >> 16) & 0xff, (cb >> 16) & 0xff, t);
	g = ft_intrapolate((ca >> 8) & 0xff, (cb >> 8) & 0xff, t);
	b = ft_intrapolate(ca & 0xff, cb & 0xff, t);
	return (r << 16 | g << 8 | b);
}

int	gradiant(int color, float t)
{
	int	r;
	int	g;
	int	b;

	r = t * (color >> 16 & 0xff);
	g = t * (color >> 8 & 0xff);
	b = t * (color & 0xff);
	return (r << 16 | g << 8 | b);
}
