/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:11:50 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/01/25 19:00:22 by mzeggaf          ###   ########.fr       */
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

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

# define MOUSE_LEFT 1
# define MOUSE_RIGHT 2
# define MOUSE_MIDDLE 3
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

# define ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

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
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_map
{
	int		width;
	int		height;
	int		altitude;
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
void	ft_draw_line(t_point a, t_point b, t_image *img, t_map *map);
// void	ft_draw_line2(t_point s, t_point e, t_image *env);
void	ft_draw_map(t_map *map, t_image *img);
void	ft_insert_pixel(int input_x, int input_y, int color, t_image *img);
int		ft_atoi_hex(char *hex);
// void	ft_isometric_projection(t_map *map);
// void	plotLine(t_point *pt0, t_point *pt1, t_image *img);
void	ft_adjust_zoom(t_point *vector, t_map *map, int zoom);
void	ft_rotate_vector(t_point *point, t_map *map);
void	ft_position_vector(t_point *vector, t_map *map, int zoom);
int		ft_abs(int nbr);
int		ft_gradiant(int color, double t);

#endif
