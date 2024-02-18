/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 11:48:12 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/18 18:08:34 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_map_error(t_map *map, char *str, int c)
{
	ft_putstr_fd("\033[0;31m", 2);
	ft_putstr_fd(map->name, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\'", 2);
	ft_putnbr_fd(c, 2);
	ft_putstr_fd("\' on line ", 2);
	ft_putnbr_fd(map->height + 1, 2);
	ft_putstr_fd("\033[0m\n", 2);
	exit(EXIT_FAILURE);
}

void	ft_validate_map(char *buffer, int rd, t_map *map, int *x)
{
	int	i;

	i = 0;
	while (i < rd)
	{
		if (buffer[i] == ' ')
			i++;
		else if (buffer[i] == '\n')
		{
			if (!map->width)
				map->width = *x;
			if (*x == map->width)
				map->height++;
			else
				ft_map_error(map, ": inconsistent map width: ", buffer[i]);
			*x = 0;
			i++;
		}
		else if (ft_isdigit(buffer[i]) || buffer[i] == '-')
		{
			if (buffer[i] == '-')
				i++;
			while (buffer[i] && ft_isdigit(buffer[i]))
				i++;
			if (!ft_strncmp(buffer + i, ",0x", 3))
			{
				i += 3;
				while (buffer[i] && ft_isdigit(buffer[i]) || \
						ft_strchr("abcdefABCDEF", buffer[i]))
					i++;
			}
			if (buffer[i] && !ft_isdigit(buffer[i]))
			{
				ft_printf("%c", buffer[i]);
				*x += 1;
			}
		}
		else
			ft_map_error(map, ": invalid character in map: ", *x);
	}
	// ft_printf("d: %d, %d\n", map->height, map->width);
}
