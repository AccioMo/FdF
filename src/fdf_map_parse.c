/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 11:48:12 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/21 12:21:02 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_map_error(t_map *map, char *str, int c, int lno)
{
	ft_putstr_fd("\033[0;31m", 2);
	ft_putstr_fd(map->name, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\'", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\' on line ", 2);
	ft_putnbr_fd(lno + 1, 2);
	ft_putstr_fd("\033[0m\n", 2);
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

static int	ft_invalid_value(char *value, t_map *map, int lno)
{
	int	i;

	i = 0;
	if (value[i] == '-')
		i++;
	while (value[i] && value[i] != '\n')
	{
		if (ft_isdigit(value[i]))
			i++;
		else if (!ft_strncmp(value + i, ",0x", 3))
		{
			i += 3;
			while (value[i] && (ft_isdigit(value[i]) || \
					ft_strchr("abcdefABCDEF", value[i])))
				i++;
		}
		else
		{
			ft_map_error(map, ": invalid character: ", value[i], lno);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_invalid(char **line, t_map *map)
{
	int	i;

	i = 0;
	while (i < map->width)
	{
		if (ft_invalid_value(line[i], map, i))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
