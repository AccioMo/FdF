/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:27:09 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/18 18:04:19 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_get_map_data(t_map *map)
{
	char	buffer[BUFFER_SIZE + 1];
	int		fd;
	int		rd;
	int		x;

	x = 0;
	map->width = 0;
	map->height = 0;
	buffer[BUFFER_SIZE] = '\0';
	fd = open(map->name, O_RDONLY);
	if (fd < 0)
		ft_exit(1, map->name);
	rd = read(fd, buffer, BUFFER_SIZE);
	while (rd > 0)
	{
		ft_validate_map(buffer, rd, map, &x);
		rd = read(fd, buffer, BUFFER_SIZE);
	}
	close(fd);
}

static t_point	*ft_get_row(char **input, int height, t_map *map)
{
	char	**values;
	t_point	*pos;
	int		i;

	i = 0;
	if (!input)
		return (NULL);
	pos = (t_point *)malloc((map->width + 1) * sizeof(t_point));
	if (!pos)
		return (NULL);
	while (i < map->width)
	{
		pos[i].x = i;
		pos[i].y = height;
		if (ft_parse_value(&pos[i], input[i]) < 0)
			return (NULL);
		if (pos[i].z > map->max_z)
			map->max_z = pos[i].z;
		if (pos[i].z < map->min_z)
			map->min_z = pos[i].z;
		i++;
	}
	return (pos);
}

char	**ft_parse(int fd, t_map *map)
{
	char	*line;
	char	**split_line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	split_line = ft_split(line, ' ');
	free(line);
	if (!split_line)
		return (NULL);
	return (split_line);
}

void	ft_init_map(t_map **map, int *fd)
{
	ft_get_map_data(*map);
	(*map)->map = (t_point **)malloc(((*map)->height + 1) * sizeof(t_point *));
	if (!(*map)->map)
		ft_exit(3, "error allocating map.\n");
	(*map)->map[(*map)->height] = NULL;
	*fd = open((*map)->name, O_RDONLY);
	if (*fd < 0)
	{
		ft_free((void **)(*map)->map);
		ft_exit(1, (*map)->name);
	}
}

void	ft_get_map(t_map *map)
{
	char	**column;
	int		fd;
	int		i;

	i = 0;
	ft_init_map(&map, &fd);
	while (i < map->height)
	{
		column = ft_parse(fd, map);
		map->map[i] = ft_get_row(column, i, map);
		ft_free((void **)column);
		if (!map->map[i])
		{
			ft_free((void **)map->map);
			close(fd);
			exit(1);
		}
		i++;
	}
	close(fd);
}
