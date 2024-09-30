/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:41:47 by mschulme          #+#    #+#             */
/*   Updated: 2023/06/03 20:53:36 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractal.h"

static int	ft_isblank(char str)
{
	return (str == ' ' || (str >= 9 && str <= 13));
}

static void	comp(t_data *data, const char *str)
{
	while (ft_isblank(*str) == 1 && *str)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			data->sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		data->res = data->res * 10 + *str++ - '0';
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
			data->res2 = data->res2 * 10 + *str++ - '0';
		while (data->res2 > 1)
			data->res2 = data->res2 / 10;
	}
	if (*str != '\0')
		exitfunction(data);
}

double	ft_atof(t_data *data, const char *str)
{
	data->res = 0;
	data->res2 = 0;
	data->sign = 1;
	comp(data, str);
	return ((data->res + data->res2) * data->sign);
}
