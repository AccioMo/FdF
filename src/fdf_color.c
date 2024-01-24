/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:09:55 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/01/23 23:30:02 by mzeggaf          ###   ########.fr       */
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
	int		nbr;

	nbr = 0;
	while (*hex)
		nbr = (nbr * 16) + ft_index(*hex++, LOWER_HEX);
	return (nbr);
}

int	ft_intrapolate(int r0, int r1, float t)
{
	return (r0 + (r1 - r0) * t);
}

int	ft_gradiant(t_point *pt0, t_point *pt1, float t)
{
	int	r;
	int	g;
	int	b;

	r = ft_intrapolate((pt0->color >> 16) & 0xff, (pt1->color >> 16) & 0xff, t);
	g = ft_intrapolate((pt0->color >> 8) & 0xff, (pt0->color >> 8) & 0xff, t);
	b = ft_intrapolate(pt0->color & 0xff, pt0->color & 0xff, t);
	// ft_printf("r: %d, g: %d, b: %d\n", r, g, b);
	return (r << 16 | g << 8 | b);
}
