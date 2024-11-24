/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:33:13 by mschulme          #+#    #+#             */
/*   Updated: 2023/05/09 14:33:13 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractal.h"

void	ft_initialise(t_data *data)
{
	data->color = 0xFFFFFF;
	data->width = 800;
	data->height = 600;
	data->minre = -2.1;
	data->maxre = 0.6;
	data->minim = -1.2;
	data->maxim = 1.2;
	data->maxiterations = 150;
	data->c_im = 0;
	data->c_re = 0;
	data->z_re = 0;
	data->z_im = 0;
	data->z_re2 = 0;
	data->z_im2 = 0;
	data->x = 0;
	data->y = 0;
	data->n = 0;
	data->isinside = true;
	data->red = 13;
	data->green = 11;
	data->blue = 7;
}

int	exitfunction(t_data *data)
{
	write(1, "Thank you for using my Fractol program. \n \
		Use Mandelbrot, Julia or Burningship as input.\n", 92);
	mlx_destroy_image(data->mlx, data->img.mlx_img);
	mlx_destroy_window(data->mlx, data->win);
	free(data);
	exit (0);
}

int	rgb_to_int(int r, int g, int b)
{
	return ((r * 256 * 256) + (g * 256) + b);
}

void	img_pix_put(t_img *img, unsigned int x, unsigned int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	ft_initarr(t_data *data)
{
	int	i;
	int	red;
	int	green;
	int	blue;

	i = 1;
	while (i <= 256)
	{
		red = data->red * (256 - i) % 256;
		green = data->green * (256 - i) % 256;
		blue = data->blue * (256 - i) % 256;
		data->arr[i - 1] = rgb_to_int(red, green, blue);
		i++;
	}
}
