/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:11:16 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/17 16:30:07 by mzeggaf          ###   ########.fr       */
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

void	ft_set_params(t_map *map)
{
	map->zoom = ft_min(WIN_WIDTH / map->width / 2, WIN_HEIGHT / map->height / 2);
	map->x_offset = (WIN_WIDTH - map->width * map->zoom) / 2;
	map->y_offset = (WIN_HEIGHT - map->height * map->zoom) / 2;
	map->x_angle = -0.615472907;
	map->y_angle = -0.523599;
	map->z_angle = 0.615472907;
	printf("%d, %d, %d, %f, %f, %f\n", map->zoom, map->x_offset, map->y_offset, map->x_angle, map->y_angle, map->z_angle);
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
	else if (keycode == KEY_S)
	{
		env->map.y_offset -= 5;
		ft_draw_map(env);
	}
	else if (keycode == KEY_W)
	{
		env->map.y_offset += 5;
		ft_draw_map(env);
	}
}

void	ft_mlx_rotate(int keycode, t_env *env)
{
	if (keycode == KEY_LEFT)
	{
		env->map.x_angle -= 0.01;
		ft_draw_map(env);
	}
	else if (keycode == KEY_RIGHT)
	{
		env->map.x_angle += 0.01;
		ft_draw_map(env);
	}
	else if (keycode == KEY_DOWN)
	{
		env->map.y_angle -= 0.01;
		ft_draw_map(env);
	}
	else if (keycode == KEY_UP)
	{
		env->map.y_angle -= 0.01;
		ft_draw_map(env);
	}
}

int	ft_key_event(int keycode, void *env)
{
	if (keycode == ESC)
		ft_end(env);
	else if ((keycode >= 0 && keycode <= 2) || keycode == 13)
		ft_mlx_move(keycode, env);
	else if (keycode >= 123 && keycode <= 126)
		ft_mlx_rotate(keycode, env);
	else if (keycode == SPACE)
	{
		ft_set_params(&((t_env *)env)->map);
		ft_draw_map(env);
	}
	else if (keycode == KEY_PLUS || keycode == KEY_PLUS_)
	{
		((t_env *)env)->map.zoom += 5;
		ft_draw_map(env);
	}
	else if (keycode == KEY_MINUS || keycode == KEY_MINUS_)
	{
		((t_env *)env)->map.zoom -= 5;
		ft_draw_map(env);
	}
	return (0);
}

double	ft_reset_angles(double angle)
{
	if (angle >= M_PI)
		return (-2 * M_PI - angle);
	else if (angle <= -M_PI)
		return (2 * M_PI + angle);
	return (angle);
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
		env->map.x_angle += (x - env->mouse.x) * 0.002;
		env->map.y_angle += (y - env->mouse.y) * 0.002;
		ft_reset_angles(env->map.x_angle);
		ft_reset_angles(env->map.y_angle);
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
	else
	{
		env->mouse.click = mousecode;
		env->mouse.x = x - env->map.x_offset;
		env->mouse.y = y - env->map.y_offset;
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
	mlx_key_hook(env.win, ft_key_event, (void *)&env);
	mlx_hook(env.win, ON_MOUSEMOVE, 0, ft_mouse_move, (void *)&env);
	mlx_hook(env.win, ON_MOUSEDOWN, 0, ft_mouse_down, (void *)&env);
	mlx_hook(env.win, ON_MOUSEUP, 0, ft_mouse_up, (void *)&env);
	mlx_hook(env.win, ON_DESTROY, 0, ft_end, (void *)&env);
	ft_draw_map(&env);
	mlx_loop(env.mlx);
}
