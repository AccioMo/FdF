/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_input_1_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 23:04:47 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/21 18:47:41 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	ft_mlx_rotate(int keycode, t_env *env)
{
	if (keycode == KEY_8 || keycode == KEY_2)
	{
		if (keycode == KEY_8)
			env->map.x_angle -= 0.02;
		else if (keycode == KEY_2)
			env->map.x_angle += 0.02;
		ft_angle_overflow(&env->map.x_angle);
	}
	else if (keycode == KEY_4 || keycode == KEY_6)
	{
		if (keycode == KEY_4)
			env->map.y_angle -= 0.02;
		else if (keycode == KEY_6)
			env->map.y_angle += 0.02;
		ft_angle_overflow(&env->map.y_angle);
	}
	else if (keycode == KEY_7 || keycode == KEY_9)
	{
		if (keycode == KEY_7)
			env->map.z_angle -= 0.02;
		else if (keycode == KEY_9)
			env->map.z_angle += 0.02;
		ft_angle_overflow(&env->map.z_angle);
	}
	ft_draw_map(env);
}

static void	ft_project_keys(int keycode, t_env *env)
{
	if (keycode == KEY_I)
	{
		env->map.projection = ISOMETRIC;
		ft_set_params(&env->map);
		ft_draw_map(env);
	}
	else if (keycode == KEY_P)
	{
		env->map.projection = PLAN;
		env->map.x_offset = (W_WIDTH - (env->map.width * env->map.zoom)) / 2;
		env->map.y_offset = W_HEIGHT / 3;
		ft_projection(&env->map);
		ft_draw_map(env);
	}
	else if (keycode == KEY_E)
	{
		env->map.projection = ELEVATION;
		env->map.x_offset = (W_WIDTH - (env->map.width * env->map.zoom)) / 2;
		env->map.y_offset = W_HEIGHT / 2;
		ft_projection(&env->map);
		ft_draw_map(env);
	}
}

static void	ft_zoom_keys(int keycode, t_env *env)
{
	if (keycode == KEY_PLUS)
	{
		env->map.zoom += 5;
		ft_draw_map(env);
	}
	else if (keycode == KEY_MINUS)
	{
		env->map.zoom -= 5;
		ft_draw_map(env);
	}
}

static void	ft_change_z_keys(int keycode, t_env *env)
{
	if (keycode == KEY_PLUS_)
	{
		env->map.z_factor += 0.05;
		ft_draw_map(env);
	}
	else if (keycode == KEY_MINUS_)
	{
		env->map.z_factor -= 0.05;
		ft_draw_map(env);
	}
}

int	ft_key_event(int keycode, void *env)
{
	t_map	*map;

	map = &((t_env *)env)->map;
	if (keycode == ESC)
		ft_end(env);
	else if (!ft_mlx_move(keycode, env))
		return (0);
	else if (keycode >= 83 && keycode <= 92)
		ft_mlx_rotate(keycode, env);
	else if (keycode == KEY_I || keycode == KEY_P || keycode == KEY_E)
		ft_project_keys(keycode, env);
	else if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		ft_zoom_keys(keycode, env);
	else if (keycode == KEY_PLUS_ || keycode == KEY_MINUS_)
		ft_change_z_keys(keycode, env);
	else if (keycode == SPACE)
	{
		map->x_offset = (W_WIDTH - (map->width * map->zoom) / 2) / 2;
		map->y_offset = (W_HEIGHT - (map->height * map->zoom) / 2) / 2;
		ft_draw_map(env);
	}
	return (0);
}
