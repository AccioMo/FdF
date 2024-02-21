/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:16:26 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/21 13:17:53 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_print_info_2(void *mlx, void *win, t_map *map, int mo)
{
	char	*word;
	int		y;

	y = W_HEIGHT / 2 + 200;
	word = ft_itoa(map->zoom);
	mlx_string_put(mlx, win, mo + 50, y += 40, 0xBBBEC0, "Zoom: ");
	mlx_string_put(mlx, win, mo + 150, y, 0xBBBEC0, word);
	free(word);
	word = ft_itoa(map->x_angle * 180 / M_PI);
	mlx_string_put(mlx, win, mo + 50, y += 40, 0xBBBEC0, "Angle X: ");
	mlx_string_put(mlx, win, mo + 150, y, 0xBBBEC0, word);
	free(word);
	word = ft_itoa(map->y_angle * 180 / M_PI);
	mlx_string_put(mlx, win, mo + 50, y += 40, 0xBBBEC0, "Angle Y: ");
	mlx_string_put(mlx, win, mo + 150, y, 0xBBBEC0, word);
	free(word);
	word = ft_itoa(map->z_angle * 180 / M_PI);
	mlx_string_put(mlx, win, mo + 50, y += 40, 0xBBBEC0, "Angle Z: ");
	mlx_string_put(mlx, win, mo + 150, y, 0xBBBEC0, word);
	free(word);
}

static void	ft_print_info(void *mlx, void *win, t_map *map, int mo)
{
	char	*word;
	int		y;

	y = W_HEIGHT / 2;
	mlx_string_put(mlx, win, mo + 25, y += 40, 0xBBBEC0, "Info:");
	word = map->name;
	mlx_string_put(mlx, win, mo + 50, y += 40, 0xBBBEC0, "Map: ");
	mlx_string_put(mlx, win, mo + 115, y, 0xBBBEC0, word);
	mlx_string_put(mlx, win, mo + 50, y += 40, 0xBBBEC0, "Projection: ");
	if (map->projection == 1)
		word = "Isometric";
	else if (map->projection == 2)
		word = "Plan";
	else if (map->projection == 3)
		word = "Elevation";
	mlx_string_put(mlx, win, mo + 175, y, 0xBBBEC0, word);
	word = ft_itoa(map->height * map->zoom);
	mlx_string_put(mlx, win, mo + 50, y += 40, 0xBBBEC0, "Height: ");
	mlx_string_put(mlx, win, mo + 150, y, 0xBBBEC0, word);
	free(word);
	word = ft_itoa(map->width * map->zoom);
	mlx_string_put(mlx, win, mo + 50, y += 40, 0xBBBEC0, "Width: ");
	mlx_string_put(mlx, win, mo + 150, y, 0xBBBEC0, word);
	free(word);
	ft_print_info_2(mlx, win, map, mo);
}

static void	ft_print_menu(void *mlx, void *win, int mo)
{
	int	y;
	int	c;

	y = 80;
	c = 0xBBBEC0;
	mlx_string_put(mlx, win, mo + 25, y, c, "How to use:");
	y += 40;
	mlx_string_put(mlx, win, mo + 35, y, c, "Scroll/+/- to zoom");
	y += 55;
	mlx_string_put(mlx, win, mo + 35, y, c, "W, A, S, and D to move");
	y += 40;
	mlx_string_put(mlx, win, mo + 35, y, c, "Left +/- to change height");
	y += 40;
	mlx_string_put(mlx, win, mo + 35, y, c, "Switch Projection:");
	y += 40;
	mlx_string_put(mlx, win, mo + 45, y, c, "I for Isometric");
	y += 40;
	mlx_string_put(mlx, win, mo + 45, y, c, "P for Plan");
	y += 40;
	mlx_string_put(mlx, win, mo + 45, y, c, "E for Elevation");
	y += 40;
	mlx_string_put(mlx, win, mo + 35, y, c, "Spacebar to center map");
	y += 40;
}

static void	ft_color_window(t_env *env, int mo, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < W_HEIGHT)
	{
		x = mo;
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
	ft_print_menu(env->mlx, env->win, W_WIDTH - 320);
	ft_print_info(env->mlx, env->win, m, W_WIDTH - 320);
}
