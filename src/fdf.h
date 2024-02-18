/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:11:50 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/18 12:29:00 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <mlx.h>
# include <time.h>
# include <math.h>
# include "../libft/libft.h"
# include "../libftprintf/ft_printf.h"
# include "../get_next_line/get_next_line.h"

# define W_WIDTH 1920
# define W_HEIGHT 1080

# define MOUSE_LEFT 1
# define MOUSE_RIGHT 2
# define MOUSE_MIDDLE 3
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_MOUSEDOWN 4
# define ON_MOUSEUP 5
# define ON_MOUSEMOVE 6
# define ON_EXPOSE 12
# define ON_DESTROY 17

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

# define KEY_1 83
# define KEY_2 84
# define KEY_3 85
# define KEY_4 86
# define KEY_5 87
# define KEY_6 88
# define KEY_7 89
# define KEY_8 91
# define KEY_9 92

# define KEY_E 14
# define KEY_P 35
# define KEY_I 34

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

typedef struct s_vector
{
	t_point	a;
	t_point	b;
	float	dx;
	int		rev;
	int		steep;
	float	gradiant;
}	t_vector;

typedef struct s_map
{
	char	*name;
	int		width;
	int		height;
	int		max_z;
	int		min_z;
	int		x_offset;
	int		y_offset;
	float	z_factor;
	float	x_angle;
	float	y_angle;
	float	z_angle;
	int		zoom;
	int		projection;
	t_point	**map;
}	t_map;

typedef struct s_mouse
{
	int	x;
	int	y;
	int	click;
}	t_mouse;
typedef struct s_env
{
	void	*mlx;
	void	*win;
	t_mouse	mouse;
	t_image	img;
	t_map	map;
}	t_env;

int		ft_key_event(int keycode, void *param);
void	ft_projection(t_map *map);
float	ft_angle_overflow(float *angle);
void	ft_set_params(t_map *map);

void	ft_print_menu(t_env *env);
float	rdecimal(float nb);
float	decimal(float nb);

int		ft_mouse_move(int x, int y, void *param);
int		ft_mouse_down(int mousecode, int x, int y, void *env);
int		ft_mouse_up(int mousecode, int x, int y, void *param);

int		ft_mlx_move(int keycode, t_env *env);
int		ft_end(void *param);

void	ft_get_map(t_map *map);
void	ft_validate_map(char *buffer, int rd, t_map *map, int *x);
void	ft_default_color(t_map *map);
int		ft_atoi_hex(char *hex);
int		ft_index(char c, char *str);
int		ft_get_len(char **ptr);

void	ft_draw_map(t_env *env);
void	ft_aa_draw(t_point *a, t_point *b, t_image *img, t_map *map);
void	ft_rotate(t_point *point, t_map *map);
void	ft_print_menu(t_env *env);

int		ft_color(int ca, int cb, t_vector *v, float t);
int		gradiant(int color, float t);
void	ft_default_color(t_map *map);

void	ft_free(void **ptr);
int		ft_exit(int code, char *str);

#endif
