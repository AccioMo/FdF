/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 09:35:57 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/18 12:40:59 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	ft_free(void **ptr)
{
	void	**hold;

	hold = ptr;
	if (!ptr)
		return ;
	while (*ptr)
		free(*ptr++);
	free(hold);
}

int	ft_index(char c, char *str)
{
	int	i;

	i = 0;
	while (*(str + i) && *(str + i) != c)
		i++;
	if (*(str + i) == '\0')
		return (-1);
	return (i);
}

float	ft_angle_overflow(float *angle)
{
	if (*angle >= M_PI)
		return (-M_PI);
	else if (*angle <= -M_PI)
		return (M_PI);
	return (*angle);
}

int	ft_parse_value(t_point *pos, char *value)
{
	char	**parsed_value;

	if (ft_strchr(value, ','))
	{
		parsed_value = ft_split(value, ',');
		if (!parsed_value)
			return (-1);
		pos->color = ft_atoi_hex(parsed_value[1]);
		pos->z = ft_atoi(parsed_value[0]);
		ft_free((void **)parsed_value);
	}
	else
	{
		pos->color = 0;
		pos->z = ft_atoi(value);
	}
	return (0);
}
