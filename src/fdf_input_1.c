/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_input_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 23:04:47 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/18 10:10:34 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

static int	ft_mlx_move(int keycode, t_env *env)
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

static int	ft_project_keys(int keycode, t_env *env)
{
	if (keycode == KEY_I)
	{
		env->map.projection = 1;
		ft_set_params(&env->map);
		ft_draw_map(env);
		return (1);
	}
	else if (keycode == KEY_P)
	{
		env->map.projection = 2;
		env->map.x_offset = (W_WIDTH - (env->map.width * env->map.zoom)) / 2;
		env->map.y_offset = W_HEIGHT / 3;
		ft_projection(&env->map);
		ft_draw_map(env);
		return (1);
	}
	else if (keycode == KEY_E)
	{
		env->map.projection = 3;
		env->map.x_offset = (W_WIDTH - (env->map.width * env->map.zoom)) / 2;
		env->map.y_offset = W_HEIGHT / 2 + 160;
		ft_projection(&env->map);
		ft_draw_map(env);
		return (1);
	}
	return (0);
}

static int	ft_zoom_keys(int keycode, t_env *env)
{
	if (keycode == KEY_PLUS || keycode == KEY_PLUS_)
	{
		env->map.zoom += 5;
		ft_draw_map(env);
		return (0);
	}
	else if (keycode == KEY_MINUS || keycode == KEY_MINUS_)
	{
		env->map.zoom -= 5;
		ft_draw_map(env);
		return (0);
	}
	return (1);
}

int	ft_key_event(int keycode, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	if (keycode == ESC)
		ft_end(env);
	else if (!ft_mlx_move(keycode, env))
		return (0);
	else if (keycode >= 83 && keycode <= 92)
		ft_mlx_rotate(keycode, env);
	else if (!ft_project_keys(keycode, env))
		return (0);
	else if (!ft_zoom_keys(keycode, env))
		return (0);
	else if (keycode == SPACE)
	{
		env->map.x_offset = (W_WIDTH - (env->map.width * env->map.zoom)) / 2;
		env->map.y_offset = (W_HEIGHT - (env->map.height * env->map.zoom)) / 2;
		ft_draw_map(env);
	}
	return (0);
}
