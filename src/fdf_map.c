/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:27:09 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/01/24 19:11:01 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_get_map_height(char *file)
{
	char	buffer[1];
	int		height;
	int		fd;

	height = 0;
	fd = open(file, O_RDONLY);
	while (read(fd, buffer, 1) > 0)
		height += ft_strchr(buffer, '\n') != NULL;
	close(fd);
	return (height);
}

void	ft_free(char **ptr)
{
	char	**hold;

	hold = ptr;
	if (!ptr)
		return ;
	while (*ptr)
		free(*ptr++);
	free(hold);
}

static t_point	*ft_get_row(char **input, int width, int height, t_map *map)
{
	t_point	*dot;
	char	**values;
	int		i;

	i = 0;
	dot = (t_point *)malloc(width * sizeof(t_point));
	if (!dot)
		return (ft_free(input), NULL);
	while (i < width)
	{
		values = ft_split(*(input + i), ',');
		if (!values)
			return(NULL);
		(dot + i)->z = ft_atoi(values[0]);
		(dot + i)->y = height;
		(dot + i)->x = i;
		if (values[1])
			(dot + i)->color = ft_atoi_hex(values[1]);
		else
			(dot + i)->color = 0x00ffffff - ft_atoi(values[0]);
		// ft_rotate_vector((dot + i), map);
		i++;
	}
	return (ft_free(input), dot);
}

int	ft_get_len(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return (0);
	while (*(ptr + i))
		i++;
	return (i);
}

// void	ft_print_map_info(t_map *map)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	ft_printf("w: %d, h: %d\n", map->width, map->height);
// 	while (i < map->height)
// 	{
// 		j = 0;
// 		while (j < map->width)
// 			ft_printf("(x: %d, y: %d, z, %d)\n", map->map[i][j++].x, map->map[i][j++].y, map->map[i][j++].z);
// 		ft_printf("\n");
// 		i++;
// 	}
// }

void	ft_get_map(char *file, t_map *map)
{
	char	*tmp_line;
	char	**tmp_split_line;
	int		fd;
	int		y;

	y = 0;
	map->height = ft_get_map_height(file);
	map->map = (t_point **)malloc(map->height * sizeof(t_point *));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror(file));
	while (y < map->height)
	{
		tmp_line = get_next_line(fd);
		tmp_split_line = ft_split(tmp_line, ' ');
		free(tmp_line);
		map->width = ft_get_len(tmp_split_line);
		*(map->map + y) = ft_get_row(tmp_split_line, map->width, y, map);
		y++;
	}
	// ft_print_map_info(map);
	close(fd);
}
