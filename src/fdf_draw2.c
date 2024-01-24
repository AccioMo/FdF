/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:39:19 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/01/24 00:49:35 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_ipart(float n)
{
	return ((int)n);
}

static void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

// void	ft_insert_pixel(int input_x, int input_y, int color, t_image *img)
// {
// 	char	*dst;
// 	int		real_x;
// 	int		real_y;

// 	if ((0 <= input_x && input_x < WINDOW_WIDTH) && (0 <= input_y && input_y < WINDOW_HEIGHT))
// 	{
// 		real_x = input_x * (img->bpp / 8);
// 		real_y = input_y * img->n_bytes;
// 		dst = img->addr + real_x + real_y;
// 		*(unsigned int *) dst = color;
// 	}
// }

// static void	ft_draw_line_loop(t_point s, t_point e, float gradient, int steep, t_image *env)
// {
// 	float	inter_y;
// 	int		x;

// 	inter_y = (float)s.y;
// 	x = s.x;
// 	while (x <= e.x)
// 	{
// 		if (steep)
// 		{
// 			ft_insert_pixel(ft_ipart(inter_y), x, 0x714674, env);
// 			ft_insert_pixel(ft_ipart(inter_y) + 1, x, 0x714674, env);
// 		}
// 		else
// 		{
// 			ft_insert_pixel(x, ft_ipart(inter_y), 0x714674, env);
// 			ft_insert_pixel(x, ft_ipart(inter_y) + 1, 0x714674, env);
// 		}
// 		inter_y += gradient;
// 		x++;
// 	}
// }

// void	ft_draw_line2(t_point s, t_point e, t_image *env)
// {
// 	float	dy;
// 	float	dx;
// 	float	gradient;
// 	int		steep;

// 	steep = ft_abs(e.y - s.y) > ft_abs(e.x - s.x);
// 	if (steep)
// 	{
// 		ft_swap(&s.x, &s.y);
// 		ft_swap(&e.x, &e.y);
// 	}
// 	if (s.x > e.x)
// 	{
// 		ft_swap(&s.x, &e.x);
// 		ft_swap(&s.y, &e.y);
// 	}
// 	dx = (float)(e.x - s.x);
// 	dy = (float)(e.y - s.y);
// 	gradient = dy / dx;
// 	if (dx == 0.0f)
// 		gradient = 1.f;
// 	ft_draw_line_loop(s, e, gradient, steep, env);
// }