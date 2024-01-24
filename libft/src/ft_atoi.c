/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 02:20:53 by mzeggaf           #+#    #+#             */
/*   Updated: 2023/11/16 16:45:35 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_longmax(const char *str)
{
	char	*long_max;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	long_max = "9223372036854775807";
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
		{
			long_max = "9223372036854775808";
			sign = -1;
		}
	}
	while (*str == '0')
		str++;
	while (*(str + i) >= '0' && *(str + i) <= '9')
		i++;
	while (*str >= '0' && *str <= '9' && i == 19)
	{
		if (*str++ > *long_max++)
			return (0);
	}
	return ((i <= 19) * sign);
}

int	ft_atoi(const char *str)
{
	int		nbr;
	char	sign;

	nbr = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	sign = is_longmax(str);
	if (sign == 0)
		return (-1 * (*str != '-'));
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = (nbr * 10) + (*str - '0') * sign;
		str++;
	}
	return (nbr);
}
