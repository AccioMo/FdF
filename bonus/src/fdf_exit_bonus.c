/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_exit_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:07:32 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/21 18:14:52 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	ft_exit(int code, char *str)
{
	ft_putstr_fd("\033[0;31m", 2);
	if (code == 1)
		perror(str);
	if (code == 2)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Invalid map extension.\n", 2);
	}
	if (code == 3)
	{
		ft_putstr_fd("FdF aborted: ", 2);
		ft_putstr_fd(str, 2);
	}
	if (code == 4)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Invalid map.\n", 2);
	}
	if (code == 5)
	{
		ft_putstr_fd("mlx: ", 2);
		ft_putstr_fd(str, 2);
	}
	ft_putstr_fd("\033[0m", 2);
	exit(EXIT_FAILURE);
}

int	ft_end(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	mlx_clear_window(env->mlx, env->win);
	mlx_destroy_image(env->mlx, env->img.img);
	mlx_destroy_window(env->mlx, env->win);
	ft_free((void **)env->map.map);
	exit(0);
	return (1);
}

void	ft_free(void **ptr)
{
	void	**hold;

	hold = ptr;
	if (!ptr)
		return ;
	while (*ptr)
		free(*ptr++);
	free(hold);
}
