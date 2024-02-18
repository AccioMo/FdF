/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:11:16 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/18 09:52:59 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	env.win = mlx_new_window(env.mlx, W_WIDTH, W_HEIGHT, "Fil de Fer");
	env.img.img = mlx_new_image(env.mlx, W_WIDTH, W_HEIGHT);
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
