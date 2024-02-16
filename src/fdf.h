/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:11:50 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/16 14:19:21 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include "../libft/libft.h"
# include "../libftprintf/ft_printf.h"
# include "../get_next_line/get_next_line.h"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define MOUSE_LEFT 1
# define MOUSE_RIGHT 2
# define MOUSE_MIDDLE 3
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

# define ESC 53
# define SPACE 49
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_PLUS_ 24
# define KEY_MINUS_ 27
# define KEY_PLUS 69
# define KEY_MINUS 78

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		n_bytes;
	int		endian;
}	t_image;

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_point;

typedef struct s_map
{
	int		width;
	int		height;
	int		max_z;
	int		min_z;
	int		x_offset;
	int		y_offset;
	int		zoom;
	t_point	**map;
}	t_map;

typedef struct s_env
{
	void	*mlx;
	void	*win;
	t_image	img;
	t_map	map;
}	t_env;

void	ft_get_map(char *file, t_map *map);
void	ft_draw_map(t_env *env);
int		ft_atoi_hex(char *hex);
void	ft_rotate(t_point *point, t_map *map);
int		ft_abs(int nbr);
int		ft_color(int color_a, int color_b, float t, int rev);
int		ft_gradiant(int color, float t);

#endif
