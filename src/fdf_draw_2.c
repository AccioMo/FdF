/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:28:45 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/18 09:58:38 by mzeggaf          ###   ########.fr       */
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

void	ft_print_menu(t_env *env)
{
	int	y;

	y = 0;
	mlx_string_put(env->mlx, env->win, 1600, y += 20, 0xffcc8f, \
		"How to use:");
	mlx_string_put(env->mlx, env->win, 1600, y += 35, 0xffcc8f, \
		"Scroll or press +/- to zoom");
	mlx_string_put(env->mlx, env->win, 1600, y += 30, 0xffcc8f, \
		"Use W, A, S, and D to move");
	mlx_string_put(env->mlx, env->win, 1600, y += 30, 0xffcc8f, \
		"Switch Projection:");
	mlx_string_put(env->mlx, env->win, 1600, y += 25, 0xffcc8f, \
		"Spacebar to reset");
	mlx_string_put(env->mlx, env->win, 1600, y += 25, 0xffcc8f, \
		"	I for Isometric");
	mlx_string_put(env->mlx, env->win, 1600, y += 25, 0xffcc8f, \
		"	P for Plan");
	mlx_string_put(env->mlx, env->win, 1600, y += 25, 0xffcc8f, \
		"	E for Elevation");
}

static void	ft_clear_map(t_image *img)
{
	int	len;
	int	i;

	i = 0;
	len = W_WIDTH * W_HEIGHT * (img->bpp / 8);
	while (i < len)
		img->addr[i++] = '\0';
}

void	ft_draw_map(t_env *env)
{
	t_map	*m;
	int		w;
	int		h;

	h = 1;
	m = &env->map;
	ft_clear_map(&env->img);
	while (h < m->height)
	{
		w = 1;
		while (w < m->width)
		{
			if (h == 1 && w < m->width)
				ft_aa_draw(&m->map[0][w - 1], &m->map[0][w], &env->img, m);
			if (w == 1 && h < m->height)
				ft_aa_draw(&m->map[h - 1][0], &m->map[h][0], &env->img, m);
			ft_aa_draw(&m->map[h][w - 1], &m->map[h][w], &env->img, m);
			ft_aa_draw(&m->map[h - 1][w], &m->map[h][w], &env->img, m);
			w++;
		}
		h++;
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	ft_print_menu(env);
}
