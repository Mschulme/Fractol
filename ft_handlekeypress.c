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

void	colors(int keysym, t_data *data)
{
	if (keysym == 15)
		data->red += 1;
	if (keysym == 17)
		data->red -= 1;
	if (keysym == 5)
		data->green += 1;
	if (keysym == 4)
		data->green -= 1;
	if (keysym == 11)
		data->blue += 1;
	if (keysym == 45)
		data->blue -= 1;
	ft_initarr(data);
}

void	arrows(int keysym, t_data *data)
{
	if (keysym == 126)
	{
		data->maxim += data->rangeim;
		data->minim += data->rangeim;
	}
	if (keysym == 125)
	{
		data->maxim -= data->rangeim;
		data->minim -= data->rangeim;
	}
	if (keysym == 124)
	{
		data->minre += data->range;
		data->maxre += data->range;
	}
	if (keysym == 123)
	{
		data->minre -= data->range;
		data->maxre -= data->range;
	}
}

int	handle_escape(int Keypress, t_data *data)
{
	data->range = (data->maxre - data->minre) * 0.08;
	data->rangeim = (data->maxim - data->minim) * 0.08;
	colors(Keypress, data);
	arrows(Keypress, data);
	if (Keypress == 53)
	{
		mlx_destroy_image(data->mlx, data->img.mlx_img);
		mlx_destroy_window(data->mlx, data->win);
		free(data);
		exit (0);
	}
	if (Keypress == 30)
		data->maxiterations += 25;
	if (Keypress == 44)
	{
		if (data->maxiterations >= 30)
			data->maxiterations -= 15;
	}
	return (0);
}

void	handle_mouse_helper(int x, int y, t_data *data)
{
	float	relx;
	float	rely;

	relx = (float) x / data->width;
	rely = (float) y / data->height;
	if (relx > 0.5)
	{
		data->minre = data->minre + data->range * (relx - 0.5);
		data->maxre = data->maxre + data->range * (relx - 0.5);
	}
	else if (relx <= 0.5)
	{
		data->minre = data->minre - data->range * (0.5 - relx);
		data->maxre = data->maxre - data->range * (0.5 - relx);
	}
	if (rely > 0.5)
	{
		data->minim = data->minim - data->range * (rely - 0.5);
		data->maxim = data->maxim - data->range * (rely - 0.5);
	}
	else if (rely <= 0.5)
	{
		data->minim = data->minim + data->range * (0.5 - rely);
		data->maxim = data->maxim + data->range * (0.5 - rely);
	}
}

int	handle_mouse(int button, int x, int y, t_data *data)
{
	data->range = (data->maxre - data->minre);
	data->rangeim = (data->maxim - data->minim);
	if (button == 4 || button == 5)
		handle_mouse_helper(x, y, data);
	data->range *= 0.15;
	data->rangeim *= 0.15;
	if (button == 5)
	{
		data->maxiterations += 5;
		data->maxre -= data->range;
		data->minre += data->range;
		data->maxim -= data->rangeim;
		data->minim += data->rangeim;
	}
	if (button == 4)
	{
		if (data->maxiterations >= 40)
			data->maxiterations -= 5;
		data->maxre += data->range;
		data->minre -= data->range;
		data->maxim += data->rangeim;
		data->minim -= data->rangeim;
	}
	return (0);
}
