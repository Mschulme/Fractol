/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:33:23 by mschulme          #+#    #+#             */
/*   Updated: 2023/05/09 14:33:23 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractal.h"

int	compmandel(t_data *data)
{
	double	q;

	q = pow(data->z_re - 0.25, 2) + pow(data->z_im, 2);
	if (q * (q + (data->z_re - 0.25)) <= 0.25 * pow(data->z_im, 2))
		return (1);
	if (pow(data->z_re + 1, 2) + pow(data->z_im, 2) <= 0.0625)
		return (1);
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
		data->z_im = (data->z_re + data->z_re) * data->z_im + data->c_im;
		data->z_re = data->z_re2 - data->z_im2 + data->c_re;
		data->n++;
	}
	return (1);
}

void	render_mandelbrot(t_data *data)
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
			compmandel(data);
			if (data->isinside == true)
				img_pix_put(&data->img, data->x, data->y, 0x000000);
			data->x = data->x + 1;
		}
		data->y = data->y + 1;
	}
}
