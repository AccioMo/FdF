/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:11:16 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/17 20:57:19 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_print_map_info(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	ft_printf("w: %d, h: %d\n", map->width, map->height);
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			ft_printf("%p ", map->map[i][j].color);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

int	ft_min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

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

void	ft_set_params(t_map *map)
{
	map->zoom = ft_min(WIN_WIDTH / map->width / 2, WIN_HEIGHT / map->height / 2);
	map->x_offset = WIN_WIDTH / 2;
	map->y_offset = (WIN_HEIGHT - (map->height * map->zoom) / 2) / 2;
	map->projection = 1;
	ft_projection(map);
}

int	ft_end(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	mlx_destroy_image(env->mlx, env->img.img);
	mlx_destroy_window(env->mlx, env->win);
	ft_free((void **)env->map.map);
	exit(0);
	return (1);
}

void	ft_mlx_move(int keycode, t_env *env)
{
	if (keycode == KEY_A)
	{
		env->map.x_offset -= 5;
		ft_draw_map(env);
	}
	else if (keycode == KEY_D)
	{
		env->map.x_offset += 5;
		ft_draw_map(env);
	}
	else if (keycode == KEY_W)
	{
		env->map.y_offset -= 5;
		ft_draw_map(env);
	}
	else if (keycode == KEY_S)
	{
		env->map.y_offset += 5;
		ft_draw_map(env);
	}
}

float	ft_angle_overflow(float angle)
{
	if (angle >= M_PI)
		return (-M_PI);
	else if (angle <= -M_PI)
		return (M_PI);
	return (angle);
}

void	ft_mlx_rotate(int keycode, t_env *env)
{
	if (keycode == KEY_8)
	{
		env->map.x_angle -= 0.02;
		ft_angle_overflow(env->map.x_angle);
		ft_draw_map(env);
	}
	else if (keycode == KEY_2)
	{
		env->map.x_angle += 0.02;
		ft_angle_overflow(env->map.x_angle);
		ft_draw_map(env);
	}
	else if (keycode == KEY_4)
	{
		env->map.y_angle -= 0.02;
		ft_angle_overflow(env->map.y_angle);
		ft_draw_map(env);
	}
	else if (keycode == KEY_6)
	{
		env->map.y_angle += 0.02;
		ft_angle_overflow(env->map.y_angle);
		ft_draw_map(env);
	}
	else if (keycode == KEY_7)
	{
		env->map.z_angle -= 0.02;
		ft_angle_overflow(env->map.z_angle);
		ft_draw_map(env);
	}
	else if (keycode == KEY_9)
	{
		env->map.z_angle += 0.02;
		ft_angle_overflow(env->map.z_angle);
		ft_draw_map(env);
	}
}

int	ft_key_event(int keycode, void *param)
{
	t_env *	env;

	env = (t_env *)param;
	if (keycode == ESC)
		ft_end(env);
	else if ((keycode >= 0 && keycode <= 2) || keycode == 13)
		ft_mlx_move(keycode, env);
	else if (keycode >= 83 && keycode <= 92)
		ft_mlx_rotate(keycode, env);
	else if (keycode == SPACE)
	{
		env->map.x_offset = (WIN_WIDTH - (env->map.width * env->map.zoom)) / 2;
		env->map.y_offset = (WIN_HEIGHT - (env->map.height * env->map.zoom)) / 2;
		ft_draw_map(env);
	}
	else if (keycode == KEY_I)
	{
		env->map.projection = 1;
		ft_set_params(&env->map);
		ft_draw_map(env);
	}
	else if (keycode == KEY_P)
	{
		env->map.projection = 2;
		env->map.x_offset = (WIN_WIDTH - (env->map.width * env->map.zoom)) / 2;
		env->map.y_offset = (WIN_HEIGHT - (env->map.height * env->map.zoom) / 2) / 2;
		ft_projection(&env->map);
		ft_draw_map(env);
	}
	else if (keycode == KEY_E)
	{
		env->map.projection = 3;
		env->map.x_offset = (WIN_WIDTH - (env->map.width * env->map.zoom)) / 2;
		env->map.y_offset = (WIN_HEIGHT - (env->map.height * env->map.zoom)) / 2;
		ft_projection(&env->map);
		ft_draw_map(env);
	}
	else if (keycode == KEY_PLUS || keycode == KEY_PLUS_)
	{
		env->map.zoom += 5;
		ft_draw_map(env);
	}
	else if (keycode == KEY_MINUS || keycode == KEY_MINUS_)
	{
		env->map.zoom -= 5;
		ft_draw_map(env);
	}
	// ft_printf("%d\n", keycode);
	return (0);
}

int	ft_mouse_move(int x, int y, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	if (env->mouse.click == MOUSE_LEFT)
	{
		env->map.x_offset = x - env->mouse.x;
		env->map.y_offset = y - env->mouse.y;
		env->mouse.x = x - env->map.x_offset;
		env->mouse.y = y - env->map.y_offset;
		ft_draw_map(env);
	}
	else if (env->mouse.click == MOUSE_RIGHT)
	{
		env->map.x_angle += (x - env->mouse.x) * 0.001;
		env->map.y_angle += (y - env->mouse.y) * 0.001;
		env->map.x_angle = ft_angle_overflow(env->map.x_angle);
		env->map.y_angle = ft_angle_overflow(env->map.y_angle);
		env->mouse.x = x;
		env->mouse.y = y;
		ft_draw_map(env);
	}
	return (0);
}

int	ft_mouse_down(int mousecode, int x, int y, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	if (mousecode == MOUSE_SCROLL_UP)
	{
		if (env->map.zoom > 5)
			env->map.zoom -= 5;
		ft_draw_map(env);
	}
	else if (mousecode == MOUSE_SCROLL_DOWN)
	{
		env->map.zoom += 5;
		ft_draw_map(env);
	}
	else if (mousecode == MOUSE_LEFT)
	{
		env->mouse.click = mousecode;
		env->mouse.x = x - env->map.x_offset;
		env->mouse.y = y - env->map.y_offset;
	}
	else if (mousecode == MOUSE_RIGHT)
	{
		env->mouse.click = mousecode;
		env->mouse.x = x;
		env->mouse.y = y;
	}
	return (0);
}

int	ft_mouse_up(int mousecode, int x, int y, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	env->mouse.click = 0;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_env	env;

	if (argc != 2)
		return (ft_putstr_fd("usage: ./fdf [map_name].fdf\n", 2), EXIT_SUCCESS);
	env.map.max_z = INT_MIN;
	env.map.min_z = INT_MAX;
	ft_get_map(*(argv + 1), &env.map);
	ft_default_color(&env.map);
	ft_set_params(&env.map);
	// ft_print_map_info(&env.map);
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WIN_WIDTH, WIN_HEIGHT, "Fil de Fer");
	env.img.img = mlx_new_image(env.mlx, WIN_WIDTH, WIN_HEIGHT);
	env.img.addr = mlx_get_data_addr(env.img.img, &env.img.bpp, \
		&env.img.n_bytes, &env.img.endian);
	if (!env.img.addr)
		return (-1);
	mlx_hook(env.win, ON_KEYDOWN, 0, ft_key_event, (void *)&env);
	mlx_hook(env.win, ON_MOUSEMOVE, 0, ft_mouse_move, (void *)&env);
	mlx_hook(env.win, ON_MOUSEDOWN, 0, ft_mouse_down, (void *)&env);
	mlx_hook(env.win, ON_MOUSEUP, 0, ft_mouse_up, (void *)&env);
	mlx_hook(env.win, ON_DESTROY, 0, ft_end, (void *)&env);
	ft_draw_map(&env);
	mlx_loop(env.mlx);
}
