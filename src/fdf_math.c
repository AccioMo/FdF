/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:34:02 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/01/24 19:17:00 by mzeggaf          ###   ########.fr       */
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

void	ft_sbzero(double vector[3])
{
	int	i;

	i = 0;
	while (i < 3)
		vector[i] = 0;
}

void	ft_mul_matrix(double basis[3][3], double vector[3], double result[3])
{
	int		i;
	int		j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		result[i] = 0;
		while (j < 3)
		{
			result[i] += (vector[j] * basis[i][j]);
			j++;
		}
		i++;
	}
}

void	ft_3d_mul_matrix(double mx1[3][3], double mx2[3][3], double res[3][3])
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			res[i][j] = 0;
			k = 0;
			while (k < 3)
			{
				res[i][j] += mx1[i][k] * mx2[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
}

void	ft_position_vector(t_point *vector, t_map *map, int zoom)
{
	int	x_pos;
	int	y_pos;

	x_pos = WINDOW_WIDTH / 2 - (zoom * map->width / 2);
	y_pos = WINDOW_HEIGHT / 2 - (zoom * map->height / 2);
	vector->x = vector->x + x_pos;
	vector->y = vector->y + y_pos;
	vector->z = vector->z;
}

void	ft_adjust_zoom(t_point *vector, t_map *map, int zoom)
{
	vector->x *= zoom;
	vector->y *= zoom;
	vector->z *= zoom * 0.6;
}

void	ft_rotate_vector(t_point *point, t_map *map)
{
	// double	mx1[3][3];
	// double	mx2[3][3];
	// double	mx3[3][3];
	// double	basis[3][3];
	// double	rotated_vector[3];
	// double	vector[3];
	ft_adjust_zoom(point, map, map->zoom);
	ft_rotate_x(point, -0.615472907);
	ft_rotate_y(point, -0.523599);
	ft_rotate_z(point, M_PI / 6);
	ft_position_vector(point, map, map->zoom);
}

// void	ft_isometric_projection(t_map *map)
// {
// 	int		i;
// 	int		j;
// 	int		x;
// 	int		y;
// 	int		z;
// 	double	rad;

// 	rad = 13 * M_PI / 6;

// 	i = 0;
// 	while (i < map->height)
// 	{
// 		j = 0;
// 		while (j < map->width)
// 		{
// 			ft_adjust_zoom(&map->map[i][j], map, 30);
// 			ft_rotate_vector(&map->map[i][j], -0.615472907, 'x', map);
// 			ft_position_vector(&map->map[i][j], map, 30);
// 			j++;
// 		}
// 		i++;
// 	}
// }
