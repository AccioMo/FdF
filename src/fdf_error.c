/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:07:32 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/18 12:17:53 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_exit(int code, char *str)
{
	ft_putstr_fd("\033[0;31m", 2);
	if (code == 1)
		perror(str);
	if (code == 2)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": invalid map extension.\n", 2);
	}
	if (code == 3)
	{
		ft_putstr_fd("malloc: ", 2);
		ft_putstr_fd(str, 2);
	}
	if (code == 4)
	{
		ft_putstr_fd("map: ", 2);
		ft_putstr_fd(str, 2);
	}
	if (code == 5)
	{
		ft_putstr_fd("mlx: ", 2);
		ft_putstr_fd(str, 2);
	}
	ft_putstr_fd("\033[0m", 2);
	exit(EXIT_FAILURE);
}
