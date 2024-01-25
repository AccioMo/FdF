/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:19:20 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/01/25 19:02:02 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw_pixel(int input_x, int input_y, double transparency, t_image *img)
{
	t_point	pt;
	char	*dst;
	int		real_x;
	int		real_y;
	int		color;

	// printf("f: %f\n", transparency);
	color = ft_gradiant(0x00ffffff, transparency);
	if ((0 <= input_x && input_x < WINDOW_WIDTH) && (0 <= input_y && input_y < WINDOW_HEIGHT))
	{
		real_x = input_x * (img->bpp / 8);
		real_y = input_y * img->n_bytes;
		dst = img->addr + real_x + real_y;
		*(unsigned int *) dst = color;
	}
}

int	ft_round(float nb)
{
	if (nb - (int)nb >= 0.5)
		return ((int)nb + 1);
	return ((int)nb);
}

// void	ft_draw_line(t_point a, t_point b, t_image *img, t_map *map)
// {
// 	float	incr[2];
// 	float	pt[2];
// 	int		d[2];
// 	int		step;
// 	int		i;

// 	ft_rotate_vector(&a, map);
// 	ft_rotate_vector(&b, map);
// 	pt[0] = (float)a.x;
// 	pt[1] = (float)a.y;
// 	d[0] = b.x - a.x;
// 	d[1] = b.y - a.y;
// 	if (ft_abs(d[0]) > ft_abs(d[1]))
// 		step = ft_abs(d[0]);
// 	else
// 		step = ft_abs(d[1]);
// 	incr[0] = (float)d[0] / step;
// 	incr[1] = (float)d[1] / step;
// 	i = 0;
// 	while (i < step)
// 	{
// 		// a.color = ft_gradiant(a, b, 0.5);
// 		ft_insert_pixel(ft_round(pt[0]), ft_round(pt[1]), a.color, img);
// 		// ft_insert_pixel(ft_round(pt[0]) + 1, ft_round(pt[1]), a.color, img);
// 		// ft_insert_pixel(ft_round(pt[0]), ft_round(pt[1]) + 1, a.color, img);
// 		pt[0] += incr[0];
// 		pt[1] += incr[1];
// 		i++;
// 	}
// }

void	ft_swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
}

int	ft_abs(int nbr)
{
	return (nbr * (-2 * (nbr < 0) + 1));
}

double	ft_decimal(double nb)
{
	if (nb > 0)
		return (nb - (int)nb);
	else
		return (nb - ((int)nb + 1));
}

double	ft_rev_decimal(double nb)
{
	return (1 - ft_decimal(nb));
}

void ft_aa_line_draw(t_point pt0, t_point pt1, t_image *img, t_map *map)
{
	int	steep;
	int x;	

	ft_rotate_vector(&pt0, map);
	ft_rotate_vector(&pt1, map);
	steep = ft_abs(pt1.y - pt0.y) > ft_abs(pt1.x - pt0.x);
    if (steep)
    {
		ft_swap(&pt0.x, &pt0.y);
		ft_swap(&pt1.x, &pt1.y);
	}
    if (pt0.x > pt1.x)
    {
		ft_swap(&pt0.x, &pt1.x);
		ft_swap(&pt0.y, &pt1.y);
	}
    double dx = pt1.x - pt0.x;
    double dy = pt1.y - pt0.y;
    double gradient = dy/dx;
    if (dx == 0.0)
        gradient = 1;
    double intersectY = pt0.y;
	x = pt0.x;
    if (steep)
    {
		while (x <= pt1.x)
		{
			ft_draw_pixel((int)intersectY, x, ft_rev_decimal(intersectY), img);
			ft_draw_pixel((int)intersectY-1, x, ft_decimal(intersectY), img);
			intersectY += gradient;
			x++;
		}
	}
    else
    {
		while (x <= pt1.x)
		{
			ft_draw_pixel(x, (int)intersectY, ft_rev_decimal(intersectY), img);
			ft_draw_pixel(x, (int)intersectY-1,  ft_decimal(intersectY), img);
			intersectY += gradient;
			x++;
		}
	}
}

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
				ft_aa_line_draw(map->map[0][w - 1], map->map[0][w], img, map);
			if (w == 1 && h < map->height)
				ft_aa_line_draw(map->map[h - 1][0], map->map[h][0], img, map);
			ft_aa_line_draw(map->map[h][w - 1], map->map[h][w], img, map);
			ft_aa_line_draw(map->map[h - 1][w], map->map[h][w], img, map);
			w++;
		}
		h++;
	}
}
