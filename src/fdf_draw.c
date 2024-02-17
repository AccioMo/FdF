/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:19:20 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/17 18:17:38 by mzeggaf          ###   ########.fr       */
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

	if ((0 <= x && x < WIN_WIDTH) && (0 <= y && y < WIN_HEIGHT))
	{
		x *= (img->bpp / 8);
		y *= img->n_bytes;
		dst = img->addr + x + y;
		*(unsigned int *) dst = color;
	}
}

float	ft_get_step(t_vector *vector)
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

void	ft_draw_line(t_vector *v, t_image *img)
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
	vct.steep = ft_abs(vct.b.y - vct.a.y) > ft_abs(vct.b.x - vct.a.x);
	vct.gradiant = ft_get_step(&vct);
	ft_draw_line(&vct, img);
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

void	ft_print_key(t_env *env)
{
	int	y;

	y = 0;
	mlx_string_put(env->mlx, env->win, 1600, y += 20, 0xffcc8f, "How to use:");
	mlx_string_put(env->mlx, env->win, 1600, y += 35, 0xffcc8f, "Scroll or press +/- to zoom");
	mlx_string_put(env->mlx, env->win, 1600, y += 30, 0xffcc8f, "Use W, A, S, and D to move");
	mlx_string_put(env->mlx, env->win, 1600, y += 30, 0xffcc8f, "Switch Projection:");
	mlx_string_put(env->mlx, env->win, 1600, y += 25, 0xffcc8f, "Spacebar to reset");
	mlx_string_put(env->mlx, env->win, 1600, y += 25, 0xffcc8f, "	I for Isometric");
	mlx_string_put(env->mlx, env->win, 1600, y += 25, 0xffcc8f, "	P for Plan");
	mlx_string_put(env->mlx, env->win, 1600, y += 25, 0xffcc8f, "	E for Elevation");
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
				ft_aa_draw(&map->map[0][w - 1], &map->map[0][w], &env->img, map);
			if (w == 1 && h < map->height)
				ft_aa_draw(&map->map[h - 1][0], &map->map[h][0], &env->img, map);
			ft_aa_draw(&map->map[h][w - 1], &map->map[h][w], &env->img, map);
			ft_aa_draw(&map->map[h - 1][w], &map->map[h][w], &env->img, map);
			w++;
		}
		h++;
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	ft_print_key(env);
}
