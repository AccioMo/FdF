/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:22:02 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/19 15:22:06 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_positive_color(int *color, float p)
{
	if (p > 0.90)
		*color = 0xfb7e00;
	else if (p > 0.60)
		*color = 0xffbf00;
	else if (p > 0.20)
		*color = 0x4895ef;
	else
		*color = 0xb5179e;
}

static void	ft_negative_color(int *color, float p)
{
	if (p > 0.80)
		*color = 0x010057;
	else if (p > 0.40)
		*color = 0x3e0c70;
	else
		*color = 0x561c91;
}

void	ft_default_color(t_map *map)
{
	double	p;
	int		i;
	int		j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j].z >= 0 && !map->map[i][j].color)
			{
				p = map->map[i][j].z / map->max_z;
				ft_positive_color(&map->map[i][j].color, p);
			}
			else if (!map->map[i][j].color)
			{
				p = map->map[i][j].z / map->min_z;
				ft_negative_color(&map->map[i][j].color, p);
			}
			j++;
		}
		i++;
	}
}
