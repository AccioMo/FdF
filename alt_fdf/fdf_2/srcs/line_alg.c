/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_alg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:38:44 by sgoffaux          #+#    #+#             */
/*   Updated: 2024/02/16 17:55:40 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_lerp(int first, int second, double p)
{
	if (first == second)
		return (first);
	return ((int)((double)first + (second - first) * p));
}

static int	ft_get_color(int x, t_point s, t_point e, float factor)
{
	int		r;
	int		g;
	int		b;
	float	percent;

	percent = ft_abs(x - s.x) / ft_abs(e.x - s.x);
	if (s.reverse)
	{
		r = ft_lerp((e.color >> 16) & 0xFF, (s.color >> 16) & 0xFF, percent);
		g = ft_lerp((e.color >> 8) & 0xFF, (s.color >> 8) & 0xFF, percent);
		b = ft_lerp(e.color & 0xFF, s.color & 0xFF, percent);
	}
	else
	{
		r = ft_lerp((s.color >> 16) & 0xFF, (e.color >> 16) & 0xFF, percent);
		g = ft_lerp((s.color >> 8) & 0xFF, (e.color >> 8) & 0xFF, percent);
		b = ft_lerp(s.color & 0xFF, e.color & 0xFF, percent);
	}
	r *= factor;
	g *= factor;
	b *= factor;
	return ((r << 16) | (g << 8) | b);
}

static void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	ft_draw_line_loop(t_point s, t_point e, float gradient, t_fdf *env)
{
	float	inter_y;
	int		x;

	inter_y = (float)s.y;
	x = s.x;
	while (x <= e.x)
	{
		if (env->steep)
		{
			ft_put_pixel(env, ft_ipart(inter_y), x, ft_get_color(x, s, e, ft_rfpart(inter_y)));
			ft_put_pixel(env, ft_ipart(inter_y) + 1, x, ft_get_color(x, s, e, ft_fpart(inter_y)));
		}
		else
		{
			ft_put_pixel(env, x, ft_ipart(inter_y), ft_get_color(x, s, e, ft_rfpart(inter_y)));
			ft_put_pixel(env, x, ft_ipart(inter_y) + 1, ft_get_color(x, s, e, ft_fpart(inter_y)));
		}
		inter_y += gradient;
		x++;
	}
}

// void	ft_insert_pixel(int input_x, int input_y, int color, t_fdf *img)
// {
// 	char	*dst;
// 	int		real_x;
// 	int		real_y;

// 	if ((0 <= input_x && input_x < 1920) && (0 <= input_y && input_y < 1080))
// 	{
// 		real_x = input_x * (img->bpp / 8);
// 		real_y = input_y * img->size_line;
// 		dst = img->data_addr + real_x + real_y;
// 		*(unsigned int *) dst = color;
// 	}
// }

// int	ft_round(float nb)
// {
// 	if (nb - (int)nb >= 0.5)
// 		return ((int)nb + 1);
// 	return ((int)nb);
// }

// void	ft_draw_line(t_point a, t_point b, t_fdf *img)
// {
// 	int		d[2];
// 	int		step;
// 	float	incr[2];
// 	float	pt[2];
// 	int		i;

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
// 	a.color = 0x00ffffff;
// 	while (i < step)
// 	{
// 		// a.color += 1;
// 		ft_put_pixel(img, ft_round(pt[0]), ft_round(pt[1]), 0x00FFFFFF);
// 		pt[0] += incr[0];
// 		pt[1] += incr[1];
// 		i++;
// 	}
// }

void	ft_draw_line(t_point s, t_point e, t_fdf *env)
{
	float	dy;
	float	dx;
	float	gradient;

	env->steep = ft_abs(e.y - s.y) > ft_abs(e.x - s.x);
	if (env->steep)
	{
		ft_swap(&s.x, &s.y);
		ft_swap(&e.x, &e.y);
	}
	if (s.x > e.x)
	{
		ft_swap(&s.x, &e.x);
		ft_swap(&s.y, &e.y);
		s.reverse = 1;
	}
	dx = (float)(e.x - s.x);
	dy = (float)(e.y - s.y);
	gradient = dy / dx;
	if (dx == 0.0f)
		gradient = 1.f;
	ft_draw_line_loop(s, e, gradient, env);
}
