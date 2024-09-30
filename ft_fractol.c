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

#include "ft_fractal.h"
#include "libft.h"

int	render(t_data *data)
{
	t_complex	c;
	char		*str;
	char		*str2;

	c.x = -0.4;
	c.y = 0.6;
	if (ft_strncmp("Mandelbrot", data->av[1], 15) == 0)
		helper1(data);
	else if (ft_strncmp("Burningship", data->av[1], 15) == 0)
		helper3(data);
	else if (ft_strncmp("Julia", data->av[1], 10) == 0 && \
			(data->ac == 2 || data->ac == 4))
		helper2(data, c);
	else
		exitfunction(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, 0, 0);
	str = ft_itoa(data->maxiterations);
	str2 = ft_strjoin("Iterations: ", str);
	mlx_string_put(data->mlx, data->win, data->width - 120, 15, \
			0x000000, str2);
	free(str);
	free(str2);
	return (0);
}

void	createimage(t_data *data)
{
	ft_initarr(data);
	if (ft_strncmp("Julia", data->av[1], 5) == 0)
	{
		data->maxre = 2;
		data->maxiterations = 1500;
	}
	data->img.mlx_img = mlx_new_image(data->mlx, data->width, data->height);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	mlx_loop_hook(data->mlx, &render, data);
	mlx_hook(data->win, 3, 0, handle_escape, data);
	mlx_hook(data->win, 17, 0, exitfunction, data);
	mlx_hook(data->win, 4, 0, handle_mouse, data);
	mlx_loop(data->mlx);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 1)
		write(1, "Use Mandelbrot, Julia or Burningship\n", 38);
	else
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (-1);
		data->mlx = mlx_init();
		if (data->mlx == NULL)
			return (-1);
		ft_initialise(data);
		data->ac = ac;
		data->av = av;
		data->win = mlx_new_window(data->mlx, data->width \
					, data->height, "Fractal");
		if (data->win == NULL)
		{
			free(data);
			exit (1);
		}
		createimage(data);
	}
}

/*
leaks --atExit -- ./fractol Mandelbrot

norminette burningship.c ft_atof.c ft_fractal.h ft_fractol.c libft.h \
ft_handlekeypress.c ft_utils.c julia.c mandelbrot.c burningship.c 
*/
