/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:33:18 by mschulme          #+#    #+#             */
/*   Updated: 2023/05/09 14:33:18 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractal.h"

int	computationsjulia(t_data *data, int radius, t_complex c)
{
	data->z_re2 = data->z_re * data->z_re;
	data->z_im2 = data->z_im * data->z_im;
	if (data->z_re2 + data->z_im2 > radius * radius)
	{
		data->isinside = false;
		data->color = data->arr[data->n % 256];
		img_pix_put(&data->img, data->x, data->y, data->color);
		return (-1);
	}
	data->temp = data->z_re2 - data->z_im2;
	data->z_im = 2 * data->z_re * data->z_im + c.y;
	data->z_re = data->temp + c.x;
	data->n++;
	return (1);
}

void	render_julia(t_data *data, int radius, t_complex c)
{
	data->re_factor = (data->maxre - data->minre) / (data->width - 1);
	data->im_factor = (data->maxim - data->minim) / (data->height - 1);
	data->y = 0;
	while (data->y < data->height)
	{
		data->c_im = data->maxim - data->y * data->im_factor;
		data->x = 0;
		while (data->x < data->width)
		{
			data->c_re = data->minre + data->x * data->re_factor;
			data->z_re = data->c_re;
			data->z_im = data->c_im;
			data->isinside = true;
			data->n = 0;
			while (data->n < data->maxiterations)
			{
				if (computationsjulia(data, radius, c) == -1)
					break ;
			}
			if (data->isinside == true)
				img_pix_put(&data->img, data->x, data->y, 0x000000);
			data->x = data->x + 1;
		}
		data->y = data->y + 1;
	}
}
