/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractal.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:23:57 by mschulme          #+#    #+#             */
/*   Updated: 2023/05/09 14:23:57 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FRACTAL_H
# define FT_FRACTAL_H

# include "mlx/mlx.h"

# include <omp.h>
# include <time.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_complex
{
	double	x;
	double	y;
}	t_complex;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;


typedef struct s_rgb
{
    int r;
    int g;
    int b;
} RGB;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_img			img;
	int				cur_img;
	long double		minre;
	long double		maxre;
	long double		minim;
	long double		maxim;
	int				height;
	int				width;
	unsigned int	maxiterations;
	unsigned int	n;
	long double		range;
	long double		rangeim;
	int				ac;
	char			**av;
	RGB 			palette[5000];
}	t_data;


int		render(t_data *data);
int		compmandel(t_data *data);
int		exitfunction(t_data *data);
void	ft_initialise(t_data *data);
void	render_mandelbrot(t_data *data);
int		handle_escape(int Keypress, t_data *data);
void	img_pix_put(t_img *img, int width, int height, int *color_cache);
int		handle_mouse(int button, int x, int y, t_data *data);

#endif
