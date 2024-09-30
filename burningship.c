/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:23:18 by mschulme          #+#    #+#             */
/*   Updated: 2023/06/06 22:50:51 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractal.h"

int	compburning(t_data *data)
{
	while (data->n < data->maxiterations)
	{
		data->z_re2 = data->z_re * data->z_re;
		data->z_im2 = data->z_im * data->z_im;
		if (data->z_re2 + data->z_im2 > 4)
		{
			data->isinside = false;
			data->color = data->arr[data->n % 256];
			img_pix_put(&data->img, data->x, data->y, data->color);
			return (-1);
		}
		data->z_im = fabsl((data->z_re + data->z_re) * data->z_im + data->c_im);
		data->z_re = fabsl(data->z_re2 - data->z_im2 + data->c_re);
		data->n++;
	}
	return (1);
}

void	render_burningship(t_data *data)
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
			compburning(data);
			if (data->isinside == true)
				img_pix_put(&data->img, data->x, data->y, 0x000000);
			data->x = data->x + 1;
		}
		data->y = data->y + 1;
	}
}
