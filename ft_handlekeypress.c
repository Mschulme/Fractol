/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlekeypress.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:33:06 by mschulme          #+#    #+#             */
/*   Updated: 2023/05/09 14:33:06 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractal.h"

void colors(int keysym, t_data *data)
{
    if (keysym == 114) // R key
        data->red += 1;
    if (keysym == 116) // T key
        data->red -= 1;
    if (keysym == 103) // G key
        data->green += 1;
    if (keysym == 104) // H key
        data->green -= 1;
    if (keysym == 98) // B key
        data->blue += 1;
    if (keysym == 110) // N key
        data->blue -= 1;
    ft_initarr(data);
}


void arrows(int keysym, t_data *data)
{
    if (keysym == 65362) // Up Arrow
    {
        data->maxim += data->rangeim;
        data->minim += data->rangeim;
    }
    if (keysym == 65364) // Down Arrow
    {
        data->maxim -= data->rangeim;
        data->minim -= data->rangeim;
    }
    if (keysym == 65363) // Right Arrow
    {
        data->minre += data->range;
        data->maxre += data->range;
    }
    if (keysym == 65361) // Left Arrow
    {
        data->minre -= data->range;
        data->maxre -= data->range;
    }
}


int handle_escape(int Keypress, t_data *data)
{
    data->range = (data->maxre - data->minre) * 0.08;
    data->rangeim = (data->maxim - data->minim) * 0.08;
    colors(Keypress, data);
    arrows(Keypress, data);
    if (Keypress == 65307) // Escape key
    {
        mlx_destroy_image(data->mlx, data->img.mlx_img);
        mlx_destroy_window(data->mlx, data->win);
        free(data);
        exit(0);
    }
    if (Keypress == 65451) // Plus key
        data->maxiterations += 25;
    if (Keypress == 65453) // Minus key
    {
        if (data->maxiterations >= 30)
            data->maxiterations -= 15;
    }
    return (0);
}


double interpolate(double start, double end, double interpolation)
{
    return start + ((end - start) * interpolation);
}

int	handle_mouse(int button, int mouse_x, int mouse_y, t_data *data)
{

	double mouseRe = (double)mouse_x / (data->width / (data->maxre - data->minre)) + data->minre;
	double mouseIm = (double)mouse_y / (data->height / (data->maxim - data->minim)) + data->minim;

	if (button == 5)
	{
		if (data->maxiterations >= 40)
			data->maxiterations -= 5;
		double zoomFactor = 0.98;
		double interpolation = 1.0 / zoomFactor;
		data->minre = interpolate(mouseRe, data->minre, interpolation);
		data->minim = interpolate(mouseIm, data->minim, interpolation);
		data->maxre = interpolate(mouseRe, data->maxre, interpolation);
		data->maxim = interpolate(mouseIm, data->maxim, interpolation);
	}

	if (button == 4)
	{
		data->maxiterations += 1;
		double zoomFactor = 1.02;
		double interpolation = 1.0 / zoomFactor;
		data->minre = interpolate(mouseRe, data->minre, interpolation);
		data->minim = interpolate(mouseIm, data->minim, interpolation);
		data->maxre = interpolate(mouseRe, data->maxre, interpolation);
		data->maxim = interpolate(mouseIm, data->maxim, interpolation);
	}
	return 0;
}
