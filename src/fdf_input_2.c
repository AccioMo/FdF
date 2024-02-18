/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_input_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 23:06:25 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/18 14:30:53 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_projection(t_map *map)
{
	if (map->projection == 1)
	{
		map->x_angle = -asin(sqrt(3) / 3);
		map->y_angle = -M_PI / 6;
		map->z_angle = asin(sqrt(3) / 3);
	}
	else if (map->projection == 2)
	{
		map->x_angle = 0;
		map->y_angle = 0;
		map->z_angle = 0;
	}
	else if (map->projection == 3)
	{
		map->x_angle = M_PI / 2;
		map->y_angle = M_PI;
		map->z_angle = M_PI;
	}
}

static int	min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

void	ft_set_params(t_map *map)
{
	map->zoom = min(W_WIDTH / map->width / 2, W_HEIGHT / map->height / 2);
	map->x_offset = (W_WIDTH - (map->width * map->zoom) / 2) / 2;
	map->y_offset = (W_HEIGHT - (map->height * map->zoom) / 2) / 2;
	map->z_factor = 0.6;
	map->projection = 1;
	ft_projection(map);
}

int	ft_mlx_move(int keycode, t_env *env)
{
	if (keycode == KEY_A)
	{
		env->map.x_offset -= 5;
		ft_draw_map(env);
		return (0);
	}
	else if (keycode == KEY_D)
	{
		env->map.x_offset += 5;
		ft_draw_map(env);
		return (0);
	}
	else if (keycode == KEY_W)
	{
		env->map.y_offset -= 5;
		ft_draw_map(env);
		return (0);
	}
	else if (keycode == KEY_S)
	{
		env->map.y_offset += 5;
		ft_draw_map(env);
		return (0);
	}
	return (1);
}

void	f(void)
{
	system("leaks fdf");
}

int	ft_end(void *param)
{
	t_env	*env;

	atexit(f);
	env = (t_env *)param;
	mlx_clear_window(env->mlx, env->win);
	mlx_destroy_image(env->mlx, env->img.img);
	mlx_destroy_window(env->mlx, env->win);
	ft_free((void **)env->map.map);
	free(env->mlx);
	exit(0);
	return (1);
}
