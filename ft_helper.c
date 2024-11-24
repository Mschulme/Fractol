/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:51:51 by mschulme          #+#    #+#             */
/*   Updated: 2023/06/06 22:54:00 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractal.h"

void	helper1(t_data *data)
{
	if (data->ac > 2)
	{
		write(1, "Additional inputs are pointless \n", 34);
		data->ac = 2;
	}
	render_mandelbrot(data);
}
