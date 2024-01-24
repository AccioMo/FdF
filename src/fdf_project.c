/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_project.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:08:27 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/01/22 12:21:20 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_rotate_vector(t_point *point, double rad, char axis, t_map *map)
{
	double	mx1[3][3];
	double	mx2[3][3];
	double	mx3[3][3];
	double	basis[3][3];
	double	rotated_vector[3];
	double	vector[3];

	if (axis == 'x')
		ft_basis_x(basis, rad);
	else if (axis == 'y')
		ft_basis_y(basis, rad);
	else if (axis == 'z')
		ft_basis_z(basis, rad);
	else
	// 	return ;
	// ft_rotate_x(point, -0.615472907);
	// ft_rotate_y(point, -0.523599);
	// ft_rotate_z(point, 0.115472907);
	// ft_basis_x(mx1, -0.615472907);
	// ft_basis_y(mx2, -0.523599);
	// ft_3d_mul_matrix(mx1, mx2, mx3);
	// ft_basis_z(mx1, 0.615472907);
	// ft_3d_mul_matrix(mx1, mx3, basis);
	vector[0] = point->x;
	vector[1] = point->y;
	vector[2] = point->z;
	// printf("x: %f | ", basis[1][1]);
	ft_mul_matrix(basis, vector, rotated_vector);
	point->x = rotated_vector[0];
	point->y = rotated_vector[1];
	point->z = rotated_vector[2];
	// printf("rx: %f | %f\n", rotated_vector[0], point->x);
}