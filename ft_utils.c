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
	data->width = 900;
	data->height = 500;
	data->minre = -2.1;
	data->maxre = 0.6;
	data->minim = -1.2;
	data->maxim = 1.2;
	data->maxiterations = 400;
}


int	exitfunction(t_data *data)
{
	write(1, "Thank you for using my Fractol program. \n \
		Use Mandelbrot.\n", 61);
	mlx_destroy_image(data->mlx, data->img.mlx_img);
	mlx_destroy_window(data->mlx, data->win);
	free(data);
	exit (EXIT_SUCCESS);
}


void img_pix_put(t_img *img, int width, int height, int *color_cache)
{
    char *base_addr = img->addr;
    int line_len = img->line_len;
    int bpp = img->bpp / 8;

    //#pragma omp parallel for collapse(2) schedule(dynamic)
    #pragma omp simd
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            char *pixel = base_addr + (y * line_len + x * bpp);
            int color = color_cache[y * width + x];
            for (int i = 0; i < bpp; ++i)
            {
                *pixel++ = (color >> (i * 8)) & 0xFF;
            }
        }
    }
}
