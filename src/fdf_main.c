/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:11:16 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/01/24 19:12:06 by mzeggaf          ###   ########.fr       */
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

int	ft_end(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	mlx_destroy_image(env->mlx, env->img.img);
	mlx_destroy_window(env->mlx, env->win);
	exit(0);
	return(1);
}

int	ft_key_event(int keycode, void *param)
{
	if (keycode == ESC)
		ft_end(param);
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
		ft_draw_map(&env->map, &env->img);
		return (0);
	}
}

int	main(int argc, char *argv[])
{
	t_env	env;

	if (argc != 2)
		return (ft_putstr_fd("usage: ./fdf [map_name].ber\n", 2), EXIT_SUCCESS);
	env.map.zoom = 60;
	ft_get_map(*(argv + 1), &env.map);
	ft_print_map_info(&env.map);
	// ft_isometric_projection(&map);
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Fil de Fer");
	env.img.img = mlx_new_image(env.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	env.img.addr = mlx_get_data_addr(env.img.img, &env.img.bpp, &env.img.n_bytes, &env.img.endian);
	ft_draw_map(&env.map, &env.img);
	mlx_put_image_to_window(env.mlx, env.win, env.img.img, 0, 0);
	mlx_key_hook(env.win, ft_key_event, (void *)&env);
	mlx_mouse_hook(env.win, ft_mouse_event, (void *)&env);
	mlx_hook(env.win, 17, 0, ft_end, (void *)&env);
	mlx_loop(env.mlx);
}
