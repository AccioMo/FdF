/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:34:02 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/16 18:41:20 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_rotate_x(t_point *point, double x_angle)
{
	int	y;

	y = point->y;
	point->y = y * cos(x_angle) + point->z * sin(x_angle);
	point->z = y * -sin(x_angle) + point->z * cos(x_angle);
}

static void	ft_rotate_y(t_point *point, double y_angle)
{
	int	x;

	x = point->x;
	point->x = x * cos(y_angle) + point->z * sin(y_angle);
	point->z = x * -sin(y_angle) + point->z * cos(y_angle);
}

static void	ft_rotate_z(t_point *point, double z_angle)
{
	int	x;
	int	y;

	x = point->x;
	y = point->y;
	point->x = x * cos(z_angle) - y * sin(z_angle);
	point->y = x * sin(z_angle) + y * cos(z_angle);
}

void	ft_position(t_point *point, t_map *map)
{
	int	x_pos;
	int	y_pos;

	point->x += map->x_offset;
	point->y += map->y_offset;
}

void	ft_zoom(t_point *point, int zoom)
{
	point->x *= zoom;
	point->y *= zoom;
	point->z *= zoom * 0.6;
}

void	ft_rotate(t_point *point, t_map *map)
{
	ft_zoom(point, map->zoom);
	ft_rotate_x(point, map->x_angle);
	ft_rotate_y(point, map->y_angle);
	ft_rotate_z(point, map->z_angle);
	ft_position(point, map);
}
