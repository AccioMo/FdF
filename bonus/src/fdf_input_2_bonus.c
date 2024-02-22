/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_input_2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 23:06:25 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/21 18:47:58 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_projection(t_map *map)
{
	if (!ft_strncmp(map->projection, ISOMETRIC, -1))
	{
		map->x_angle = -asin(sqrt(3) / 3);
		map->y_angle = -M_PI / 6;
		map->z_angle = asin(sqrt(3) / 3);
	}
	else if (!ft_strncmp(map->projection, PLAN, -1))
	{
		map->x_angle = 0;
		map->y_angle = 0;
		map->z_angle = 0;
	}
	else if (!ft_strncmp(map->projection, ELEVATION, -1))
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
	map->projection = ISOMETRIC;
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
