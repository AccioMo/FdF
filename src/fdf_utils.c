/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 09:35:57 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/18 09:36:15 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	ft_angle_overflow(float *angle)
{
	if (*angle >= M_PI)
		return (-M_PI);
	else if (*angle <= -M_PI)
		return (M_PI);
	return (*angle);
}
