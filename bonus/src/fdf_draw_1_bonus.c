/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_1_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:19:20 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/21 17:52:55 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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
	if (vector->vert)
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
	if (v->vert)
	{
		while (v->a.x <= v->b.x)
		{
			c = ft_color(v->a.color, v->b.color, v, (v->b.x - v->a.x) / v->dx);
			ft_put_pixel(v->a.y, v->a.x, gradiant(c, rdecimal(v->a.y)), img);
			ft_put_pixel(v->a.y + 1, v->a.x, gradiant(c, decimal(v->a.y)), img);
			v->a.y += v->step;
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
			v->a.y += v->step;
			v->a.x++;
		}
	}
}

static int	ft_in_screen(t_point *a, t_point *b)
{
	float	m;
	float	y;
	float	x;

	m = (b->y - a->y) / (b->x - a->x);
	y = m * (W_WIDTH - a->x) + a->y;
	if ((b->x - a->x) == 0)
		m = 1;
	if (y >= 0 && y <= W_HEIGHT)
		return (1);
	y = m * (0 - a->x) + a->y;
	if (y >= 0 && y <= W_HEIGHT)
		return (1);
	x = (W_HEIGHT - a->y) / m + a->x;
	if (x >= 0 && x <= W_WIDTH)
		return (1);
	x = (0 - a->y) / m + a->x;
	if (x >= 0 && x <= W_WIDTH)
		return (1);
	return (0);
}

void	ft_aa_draw(t_point *a, t_point *b, t_image *img, t_map *map)
{
	t_vector	vct;

	vct.a = *a;
	vct.b = *b;
	ft_rotate(&vct.a, map);
	ft_rotate(&vct.b, map);
	vct.vert = abs((int)(vct.b.y - vct.a.y)) > abs((int)(vct.b.x - vct.a.x));
	if (!ft_in_screen(&vct.a, &vct.b))
		return ;
	vct.step = ft_get_step(&vct);
	ft_draw_line(&vct, img);
}
