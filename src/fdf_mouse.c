/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:29:48 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/19 15:21:40 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_mouse_move(int x, int y, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	if (env->mouse.click == MOUSE_LEFT)
	{
		env->map.x_offset = x - env->mouse.x;
		env->map.y_offset = y - env->mouse.y;
		env->mouse.x = x - env->map.x_offset;
		env->mouse.y = y - env->map.y_offset;
		ft_draw_map(env);
	}
	else if (env->mouse.click == MOUSE_RIGHT)
	{
		env->map.x_angle += (y - env->mouse.y) * 0.001;
		env->map.y_angle += (x - env->mouse.x) * 0.001;
		env->map.x_angle = ft_angle_overflow(&env->map.x_angle);
		env->map.y_angle = ft_angle_overflow(&env->map.y_angle);
		env->mouse.x = x;
		env->mouse.y = y;
		ft_draw_map(env);
	}
	return (0);
}

int	ft_mouse_down(int mousecode, int x, int y, void *env)
{
	if (mousecode == MOUSE_SCROLL_UP)
	{
		if (((t_env *)env)->map.zoom > 5)
			((t_env *)env)->map.zoom -= 5;
		ft_draw_map(((t_env *)env));
	}
	else if (mousecode == MOUSE_SCROLL_DOWN)
	{
		((t_env *)env)->map.zoom += 5;
		ft_draw_map(((t_env *)env));
	}
	else if (mousecode == MOUSE_LEFT)
	{
		((t_env *)env)->mouse.click = mousecode;
		((t_env *)env)->mouse.x = x - ((t_env *)env)->map.x_offset;
		((t_env *)env)->mouse.y = y - ((t_env *)env)->map.y_offset;
	}
	else if (mousecode == MOUSE_RIGHT)
	{
		((t_env *)env)->mouse.click = mousecode;
		((t_env *)env)->mouse.x = x;
		((t_env *)env)->mouse.y = y;
	}
	return (0);
}

int	ft_mouse_up(int mousecode, int x, int y, void *param)
{
	t_env	*env;

	(void)x;
	(void)y;
	(void)mousecode;
	env = (t_env *)param;
	env->mouse.click = 0;
	return (0);
}
