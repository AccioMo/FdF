/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 11:48:12 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/18 12:02:57 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_map_error(t_map *map, char *str, int x)
{
	ft_putstr_fd("\033[0;31m", 2);
	ft_putstr_fd(map->name, 2);
	ft_putstr_fd(": line ", 2);
	ft_putnbr_fd(map->height + 1, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd((x + 1), 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\033[0m", 2);
	exit(EXIT_FAILURE);
}

void	ft_validate_map(char *buffer, int rd, t_map *map, int *x)
{
	int	i;

	i = 0;
	while (i < rd)
	{
		if (buffer[i] == '\n')
		{
			if (!map->width)
				map->width = *x;
			if (*x == map->width)
				map->height++;
			else
				ft_map_error(map, " :inconsistent map width.\n", *x);
			*x = 0;
		}
		else if (buffer[i] == ' ')
			*x += (buffer[i + 1] != ' ') && (buffer[i + 1] != '\n');
		else if (!ft_strchr("0123456789,xABCDEFabcdef+-", buffer[i]))
			ft_map_error(map, " :invalid character in map.\n", *x);
		i++;
	}
}
