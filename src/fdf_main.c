/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:11:16 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/19 15:20:23 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_mlx(t_env *env)
{
	env->mlx = mlx_init();
	if (!env->mlx)
		ft_exit(5, "init error.\n");
	env->win = mlx_new_window(env->mlx, W_WIDTH, W_HEIGHT, "Fil de Fer");
	if (!env->win)
		ft_exit(5, "error creating window.\n");
	env->img.img = mlx_new_image(env->mlx, W_WIDTH, W_HEIGHT);
	if (!env->img.img)
		ft_exit(5, "error creating image.\n");
	env->img.addr = mlx_get_data_addr(env->img.img, &env->img.bpp, \
		&env->img.n_bytes, &env->img.endian);
	if (!env->img.addr)
		ft_exit(5, "error initializing image data.\n");
}

int	main(int argc, char *argv[])
{
	t_env	env;

	if (argc != 2)
	{
		ft_putstr_fd("usage: ./fdf [map_name].fdf\n", 2);
		exit(EXIT_SUCCESS);
	}
	if (ft_strncmp(ft_strchr(*(argv + 1), '.'), ".fdf\0", 5) != 0)
		ft_exit(2, *(argv + 1));
	env.map.max_z = INT_MIN;
	env.map.min_z = INT_MAX;
	env.map.name = *(argv + 1);
	ft_get_map(&env.map);
	ft_default_color(&env.map);
	ft_set_params(&env.map);
	ft_init_mlx(&env);
	mlx_hook(env.win, ON_KEYDOWN, 0, ft_key_event, (void *)&env);
	mlx_hook(env.win, ON_MOUSEMOVE, 0, ft_mouse_move, (void *)&env);
	mlx_hook(env.win, ON_MOUSEDOWN, 0, ft_mouse_down, (void *)&env);
	mlx_hook(env.win, ON_MOUSEUP, 0, ft_mouse_up, (void *)&env);
	mlx_hook(env.win, ON_DESTROY, 0, ft_end, (void *)&env);
	ft_draw_map(&env);
	mlx_loop(env.mlx);
	return (0);
}
