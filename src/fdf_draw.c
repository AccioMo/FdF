/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:19:20 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/16 18:51:39 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_swap(float *a, float *b)
{
	float	c;

	c = *a;
	*a = *b;
	*b = c;
}

int	ft_abs(int nbr)
{
	return (nbr * (-2 * (nbr < 0) + 1));
}

float	ft_fpart(float nb)
{
	if (nb > 0)
		return (nb - (int)nb);
	else
		return (nb - ((int)nb + 1));
}

float	ft_rfpart(float nb)
{
	return (1 - ft_fpart(nb));
}

void	ft_put_pixel(int x, int y, int color, t_image *img)
{
	char	*dst;

	if ((0 <= x && x < WIN_WIDTH) && (0 <= y && y < WIN_HEIGHT))
	{
		x *= (img->bpp / 8);
		y *= img->n_bytes;
		dst = img->addr + x + y;
		*(unsigned int *) dst = color;
	}
}

float	ft_get_step(t_point *a, t_point *b, int steep)
{
	float	dx;
	float	dy;

	if (steep)
	{
		ft_swap(&a->x, &a->y);
		ft_swap(&b->x, &b->y);
	}
	if (a->x > b->x)
	{
		ft_swap(&a->x, &b->x);
		ft_swap(&a->y, &b->y);
	}
	dx = b->x - a->x;
	dy = b->y - a->y;
	if (dx == 0)
		return (1);
	return (dy / dx);
}

void	ft_draw_line(t_point *a, t_point *b, float step, int col, t_image *img)
{
	float	d;
	float	pos_x;
	float	pos_y;

	pos_y = a->y;
	pos_x = a->x;
	d = b->x - pos_x;
	if (col)
	{
		while (pos_x <= b->x)
		{
			col = ft_color(a->color, b->color, (b->x - pos_x) / d, a->z > b->z);
			ft_put_pixel(pos_y, pos_x, ft_gradiant(col, ft_rfpart(pos_y)), img);
			ft_put_pixel(pos_y - 1, pos_x, ft_gradiant(col, ft_fpart(pos_y)), img);
			pos_y += step;
			pos_x++;
		}
	}
	else
	{
		while (pos_x <= b->x)
		{
			col = ft_color(a->color, b->color, (b->x - pos_x) / d, a->z > b->z);
			ft_put_pixel(pos_x, pos_y, ft_gradiant(col, ft_rfpart(pos_y)), img);
			ft_put_pixel(pos_x, pos_y - 1, ft_gradiant(col, ft_fpart(pos_y)), img);
			pos_y += step;
			pos_x++;
		}
	}
}

void	ft_aa_draw(t_point a, t_point b, t_image *img, t_map *map)
{
	float	step;
	int		angle;

	ft_rotate(&a, map);
	ft_rotate(&b, map);
	angle = ft_abs(b.y - a.y) > ft_abs(b.x - a.x);
	step = ft_get_step(&a, &b, angle);
	ft_draw_line(&a, &b, step, angle, img);
}

void	ft_clear_map(t_image *img)
{
	int	len;
	int	i;

	i = 0;
	len = WIN_WIDTH * WIN_HEIGHT * (img->bpp / 8);
	while (i < len)
		img->addr[i++] = '\0';
}

void	ft_draw_map(t_env *env)
{
	t_map	*map;
	int		w;
	int		h;

	h = 1;
	map = &env->map;
	ft_clear_map(&env->img);
	while (h < map->height)
	{
		w = 1;
		while (w < map->width)
		{
			if (h == 1 && w < map->width)
				ft_aa_draw(map->map[0][w - 1], map->map[0][w], &env->img, map);
			if (w == 1 && h < map->height)
				ft_aa_draw(map->map[h - 1][0], map->map[h][0], &env->img, map);
			ft_aa_draw(map->map[h][w - 1], map->map[h][w], &env->img, map);
			ft_aa_draw(map->map[h - 1][w], map->map[h][w], &env->img, map);
			w++;
		}
		h++;
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
}
