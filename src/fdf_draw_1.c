/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:19:20 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/18 10:00:25 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_put_pixel(int x, int y, int color, t_image *img)
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

static void	ft_swap(float *a, float *b)
{
	float	c;

	c = *a;
	*a = *b;
	*b = c;
}

static float	ft_get_step(t_vector *vector)
{
	float	dx;
	float	dy;

	vector->rev = 0;
	if (vector->steep)
	{
		ft_swap(&vector->a.x, &vector->a.y);
		ft_swap(&vector->b.x, &vector->b.y);
	}
	if (vector->a.x > vector->b.x)
	{
		ft_swap(&vector->a.x, &vector->b.x);
		ft_swap(&vector->a.y, &vector->b.y);
		vector->rev = 1;
	}
	dx = vector->b.x - vector->a.x;
	dy = vector->b.y - vector->a.y;
	if (dx == 0)
		return (1);
	return (dy / dx);
}

static void	ft_draw_line(t_vector *v, t_image *img)
{
	int	c;

	v->dx = v->b.x - v->a.x;
	if (v->steep)
	{
		while (v->a.x <= v->b.x)
		{
			c = ft_color(v->a.color, v->b.color, v, (v->b.x - v->a.x) / v->dx);
			ft_put_pixel(v->a.y, v->a.x, gradiant(c, rdecimal(v->a.y)), img);
			ft_put_pixel(v->a.y + 1, v->a.x, gradiant(c, decimal(v->a.y)), img);
			v->a.y += v->gradiant;
			v->a.x++;
		}
	}
	else
	{
		while (v->a.x <= v->b.x)
		{
			c = ft_color(v->a.color, v->b.color, v, (v->b.x - v->a.x) / v->dx);
			ft_put_pixel(v->a.x, v->a.y, gradiant(c, rdecimal(v->a.y)), img);
			ft_put_pixel(v->a.x, v->a.y + 1, gradiant(c, decimal(v->a.y)), img);
			v->a.y += v->gradiant;
			v->a.x++;
		}
	}
}

void	ft_aa_draw(t_point *a, t_point *b, t_image *img, t_map *map)
{
	t_vector	vct;

	vct.a = *a;
	vct.b = *b;
	ft_rotate(&vct.a, map);
	ft_rotate(&vct.b, map);
	vct.steep = abs((int)(vct.b.y - vct.a.y)) > abs((int)(vct.b.x - vct.a.x));
	vct.gradiant = ft_get_step(&vct);
	ft_draw_line(&vct, img);
}
