/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:19:20 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/01/24 20:21:07 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_insert_pixel(int input_x, int input_y, int color, t_image *img)
{
	t_point	pt;
	char	*dst;
	int		real_x;
	int		real_y;

	if ((0 <= input_x && input_x < WINDOW_WIDTH) && (0 <= input_y && input_y < WINDOW_HEIGHT))
	{
		real_x = input_x * (img->bpp / 8);
		real_y = input_y * img->n_bytes;
		dst = img->addr + real_x + real_y;
		*(unsigned int *) dst = color;
	}
}

int	ft_abs(int nbr)
{
	return (nbr * (-2 * (nbr < 0) + 1));
}

int	ft_round(float nb)
{
	if (nb - (int)nb >= 0.5)
		return ((int)nb + 1);
	return ((int)nb);
}

void	ft_draw_line(t_point a, t_point b, t_image *img, t_map *map)
{
	float	incr[2];
	float	pt[2];
	int		d[2];
	int		step;
	int		i;

	ft_rotate_vector(&a, map);
	ft_rotate_vector(&b, map);
	pt[0] = (float)a.x;
	pt[1] = (float)a.y;
	d[0] = b.x - a.x;
	d[1] = b.y - a.y;
	if (ft_abs(d[0]) > ft_abs(d[1]))
		step = ft_abs(d[0]);
	else
		step = ft_abs(d[1]);
	incr[0] = (float)d[0] / step;
	incr[1] = (float)d[1] / step;
	i = 0;
	while (i < step)
	{
		// a.color = ft_gradiant(a, b, 0.5);
		ft_insert_pixel(ft_round(pt[0]), ft_round(pt[1]), a.color, img);
		// ft_insert_pixel(ft_round(pt[0]) + 1, ft_round(pt[1]), a.color, img);
		// ft_insert_pixel(ft_round(pt[0]), ft_round(pt[1]) + 1, a.color, img);
		pt[0] += incr[0];
		pt[1] += incr[1];
		i++;
	}
}

// void plotLine(t_point pt0, t_point pt1, t_image *img)
// {
// 	int	x0 = pt0.x;
// 	int	y0 = pt0.y;
// 	int	x1 = pt1.x;
// 	int	y1 = pt1.y;
// 	int sx = x0 < x1 ? 1 : -1;
// 	int sy = y0 < y1 ? 1 : -1;
// 	int P;
// 	int dx = abs(x1 - x0);
// 	int dy = -abs(y1 - y0);
// 	int error = dx + dy;

// 	while (x0 != x1 || y0 != y1)
// 	{
// 		ft_insert_pixel(x0, y0, 0x00FFFFFF, img);
// 		// if (x0 == x1 && y0 == y1)
// 		// 	break;
// 		P = 2 * error;
// 		if (P >= dy) {
// 			if (x0 == x1)
// 				break;
// 			error += dy;
// 			x0 += sx;
// 		}
// 		if (P <= dx) {
// 			if (y0 == y1)
// 				break;
// 			error += dx;
// 			y0 += sy;
// 		}
// 	}
// }

void	ft_draw_map(t_map *map, t_image *img)
{
	int	w;
	int	h;

	h = 1;
	while (h < map->height)
	{
		w = 1;
		while (w < map->width)
		{
			if (h == 1 && w < map->width)
				ft_draw_line(map->map[0][w - 1], map->map[0][w], img, map);
			if (w == 1 && h < map->height)
				ft_draw_line(map->map[h - 1][0], map->map[h][0], img, map);
			ft_draw_line(map->map[h][w - 1], map->map[h][w], img, map);
			ft_draw_line(map->map[h - 1][w], map->map[h][w], img, map);
			w++;
		}
		h++;
	}
}
