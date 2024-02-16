/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:09:55 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/16 18:50:02 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_index(char c, char *str)
{
	int	i;

	i = 0;
	while (*(str + i) && *(str + i) != c)
		i++;
	if (*(str + i) == '\0')
		return (-1);
	return (i);
}

int	ft_atoi_hex(char *hex)
{
	unsigned int	nbr;

	nbr = 0;
	while (*hex)
		nbr = (nbr * 16) + ft_index(*hex++, LOWER_HEX);
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

int	ft_color(int color_a, int color_b, float t, int rev)
{
	int	ts;
	int	r;
	int	g;
	int	b;

	if (rev)
		ft_swap(&color_a, &color_b);
	// ts = ft_intrapolate((color_a >> 24) & 0xff, (color_b >> 24) & 0xff, t);
	r = ft_intrapolate((color_a >> 16) & 0xff, (color_b >> 16) & 0xff, t);
	g = ft_intrapolate((color_a >> 8) & 0xff, (color_b >> 8) & 0xff, t);
	b = ft_intrapolate(color_a & 0xff, color_b & 0xff, t);
	return (r << 16 | g << 8 | b);
}

int	ft_gradiant(int color, float t)
{
	int	ts;
	int	r;
	int	g;
	int	b;

	// ts = t * 0xff;
	r = t * (color >> 16 & 0xff);
	g = t * (color >> 8 & 0xff);
	b = t * (color & 0xff);
	return (r << 16 | g << 8 | b);
}
