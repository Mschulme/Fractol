/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:32:56 by mschulme          #+#    #+#             */
/*   Updated: 2023/05/09 14:32:56 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_fractal.h"

RGB interpolate_color(float t)
{
    RGB color;
    color.r = (int)(fmax(0, fmin(255, 17 * (1 - t) * t * t * t * 255)));
    color.g = (int)(fmax(0, fmin(255, 6 * (1 - t) * (1 - t) * t * t * 255)));
    color.b = (int)(fmax(0, fmin(255, 1.5 * (1 - t) * (1 - t) * (1 - t) * t * 255)));
    return color;
}


void precompute_colors(RGB *palette, int max_i)
{
    for (int i = 0; i < max_i; i++)
    {
        float t = (float)i / (max_i - 1);
        palette[i] = interpolate_color(t);
    }
}


int	render(t_data *data)
{
	char		*str;
	char		*str2;

	if (ft_strncmp("Mandelbrot", data->av[1], 15) == 0)
		render_mandelbrot(data);
	else
		exitfunction(data);

	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, 0, 0);
	str = ft_itoa(data->maxiterations);
	str2 = ft_strjoin("Iterations: ", str);
	mlx_string_put(data->mlx, data->win, data->width - 120, 15, 0x000000, str2);
	free(str);
	free(str2);
	return (EXIT_SUCCESS);
}

void createimage(t_data *data)
{
    data->img.mlx_img = mlx_new_image(data->mlx, data->width, data->height);
    data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);

    mlx_loop_hook(data->mlx, &render, data);
	
    mlx_hook(data->win, 3, 1L<<1, handle_escape, data);
    mlx_hook(data->win, 17, 1L<<17, exitfunction, data);
    mlx_hook(data->win, 4, 1L<<2, handle_mouse, data);
    mlx_loop(data->mlx);
}


int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 1)
		printf("Use ./fractol Mandelbrot\n");
	else
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (-1);
		data->mlx = mlx_init();
		if (data->mlx == NULL)
			return (-1);
		ft_initialise(data);
		precompute_colors(data->palette, data->maxiterations);
		data->ac = ac;
		data->av = av;
		data->win = mlx_new_window(data->mlx, data->width, data->height, "Fractal");
		if (data->win == NULL)
		{
			free(data);
			exit (EXIT_FAILURE);
		}
		createimage(data);
	}
}
