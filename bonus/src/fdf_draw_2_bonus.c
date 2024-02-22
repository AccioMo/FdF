/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:28:45 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/21 17:52:58 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

float	decimal(float nb)
{
	if (nb > 0)
		return (nb - (int)nb);
	else
		return (nb - ((int)nb + 1));
}

float	rdecimal(float nb)
{
	return (1 - decimal(nb));
}

void	ft_put_pixel(int x, int y, int color, t_image *img)
{
	char	*dst;

	if ((0 <= x && x < W_WIDTH) && (0 <= y && y < W_HEIGHT))
	{
		x *= (img->bpp / 8);
		y *= img->n_bytes;
		dst = img->addr + x + y;
		*(unsigned int *) dst = color;
	}
}
