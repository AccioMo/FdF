/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:11:16 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/16 14:26:19 by mzeggaf          ###   ########.fr       */
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
}

int	ft_end(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	mlx_destroy_image(env->mlx, env->img.img);
	mlx_destroy_window(env->mlx, env->win);
	exit(0);
	return (1);
}

int	ft_key_event(int keycode, void *env)
{
	if (keycode == ESC)
		ft_end(env);
	else if (keycode == KEY_A || keycode == KEY_RIGHT)
	{
		((t_env *)env)->map.x_offset -= 5;
		ft_draw_map(env);
	}
	else if (keycode == KEY_D || keycode == KEY_LEFT)
	{
		((t_env *)env)->map.x_offset += 5;
		ft_draw_map(env);
	}
	else if (keycode == KEY_S || keycode == KEY_UP)
	{
		((t_env *)env)->map.y_offset -= 5;
		ft_draw_map(env);
	}
	else if (keycode == KEY_W || keycode == KEY_DOWN)
	{
		((t_env *)env)->map.y_offset -= 5;
		ft_draw_map(env);
	}
	else if (keycode == SPACE)
	{
		ft_set_params(env);
		ft_draw_map(env);
	}
	return (0);
}

int	ft_mouse_event(int mousecode, int x, int y, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	if (mousecode == MOUSE_RIGHT)
	{
		ft_printf("hello\n");
		env->map.zoom = 30;
		ft_draw_map(env);
		return (0);
	}
	else if (mousecode == MOUSE_SCROLL_UP)
	{
		env->map.zoom += 5;
		ft_draw_map(env);
	}
	else if (mousecode == MOUSE_SCROLL_DOWN)
	{
		env->map.zoom -= 5;
		ft_draw_map(env);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_env	env;

	if (argc != 2)
		return (ft_putstr_fd("usage: ./fdf [map_name].fdf\n", 2), EXIT_SUCCESS);
	ft_get_map(*(argv + 1), &env.map);
	ft_set_params(&env.map);
	ft_print_map_info(&env.map);
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WIN_WIDTH, WIN_HEIGHT, "Fil de Fer");
	env.img.img = mlx_new_image(env.mlx, WIN_WIDTH, WIN_HEIGHT);
	env.img.addr = mlx_get_data_addr(env.img.img, &env.img.bpp, \
		&env.img.n_bytes, &env.img.endian);
	mlx_key_hook(env.win, ft_key_event, (void *)&env);
	mlx_mouse_hook(env.win, ft_mouse_event, (void *)&env);
	mlx_hook(env.win, 17, 0, ft_end, (void *)&env);
	ft_draw_map(&env);
	mlx_loop(env.mlx);
}
