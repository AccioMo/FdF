/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 11:48:12 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/19 13:54:05 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_map_error(t_map *map, char *str, int c)
{
	ft_putstr_fd("\033[0;31m", 2);
	ft_putstr_fd(map->name, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\'", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\' on line ", 2);
	ft_putnbr_fd(map->height + 1, 2);
	ft_putstr_fd("\033[0m\n", 2);
	exit(EXIT_FAILURE);
}
static char	*ft_strncpy(char *dest, char *src, int n)
{
	while (n > 0 && *src)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}
	*dest = '\0';
	return (dest);
}

static char	*ft_nrealloc(char *src, char *buffer, int n)
{
	char	*str;
	int		l_src;

	if (n < 0)
		return (src);
	l_src = ft_strlen(src);
	str = (char *)malloc(sizeof(char) * (l_src + n + 1));
	if (!str)
		return (free(src), NULL);
	ft_strncpy(ft_strncpy(str, src, l_src), buffer, n);
	if (src)
		free(src);
	return (str);
}

char	*ft_fopen(int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*contents;
	int		rd;

	rd = 1;
	contents = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (close(fd), NULL);
	buffer[BUFFER_SIZE] = '\0';
	while (rd > 0)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		contents = ft_nrealloc(contents, buffer, rd);
		if (!contents)
			return (close(fd), free(buffer), NULL);
	}
	close(fd);
	return (contents);
}

void	ft_validate_map(char *buffer, t_map *map)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (buffer[i])
	{
		if (buffer[i] == ' ')
			i++;
		else if (buffer[i] == '\n')
		{
			if (!map->width)
				map->width = x;
			if (x == map->width)
				map->height++;
			else
			{
				free(buffer);
				ft_map_error(map, ": inconsistent map width: ", buffer[i]);
			}
			x = 0;
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
				while (buffer[i] && (ft_isdigit(buffer[i]) || \
						ft_strchr("abcdefABCDEF", buffer[i])))
					i++;
			}
			x++;
		}
		else
		{
			free(buffer);
			ft_map_error(map, ": invalid character in map: ", buffer[i]);
		}
	}
}
