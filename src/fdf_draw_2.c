/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:28:45 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/19 20:30:07 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

static void	ft_print_menu(t_env *env, int menu_offset)
{
	int	y;

	y = 0;
	mlx_string_put(env->mlx, env->win, menu_offset + 25, y += 40, 0xBBBEC0, \
		"How to use:");
	mlx_string_put(env->mlx, env->win, menu_offset + 25, y += 55, 0xBBBEC0, \
		"Scroll/+/- to zoom");
	mlx_string_put(env->mlx, env->win, menu_offset + 25, y += 40, 0xBBBEC0, \
		"W, A, S, and D to move");
	mlx_string_put(env->mlx, env->win, menu_offset + 25, y += 40, 0xBBBEC0, \
		"Left +/- to change height");
	mlx_string_put(env->mlx, env->win, menu_offset + 25, y += 40, 0xBBBEC0, \
		"Switch Projection:");
	mlx_string_put(env->mlx, env->win, menu_offset + 35, y += 40, 0xBBBEC0, \
		"I for Isometric");
	mlx_string_put(env->mlx, env->win, menu_offset + 35, y += 40, 0xBBBEC0, \
		"P for Plan");
	mlx_string_put(env->mlx, env->win, menu_offset + 35, y += 40, 0xBBBEC0, \
		"E for Elevation");
	mlx_string_put(env->mlx, env->win, menu_offset + 25, y += 40, 0xBBBEC0, \
		"Spacebar to reset");
}

static void	ft_color_window(t_env *env, int menu_offset, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < W_HEIGHT)
	{
		x = menu_offset;
		while (x < W_WIDTH)
			ft_put_pixel(x++, y, color, &env->img);
		y++;
	}
}

void	ft_draw_map(t_env *env)
{
	t_map	*m;
	int		w;
	int		h;

	h = 0;
	m = &env->map;
	ft_color_window(env, 0, 0x0c121d);
	while (h < m->height)
	{
		w = 0;
		while (w < m->width)
		{
			if (w < m->width - 1)
				ft_aa_draw(&m->map[h][w], &m->map[h][w + 1], &env->img, m);
			if (h < m->height - 1)
				ft_aa_draw(&m->map[h][w], &m->map[h + 1][w], &env->img, m);
			w += 1;
		}
		h += 1;
	}
	ft_color_window(env, W_WIDTH - 325, 0x251230);
	ft_color_window(env, W_WIDTH - 320, 0x0e0712);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	ft_print_menu(env, W_WIDTH - 320);
}
