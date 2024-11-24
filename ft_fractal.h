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

# include <math.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>

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
	int				brightness;
	int				height;
	int				width;
	long double		re_factor;
	long double		im_factor;
	unsigned int	maxiterations;
	long double		c_im;
	long double		c_re;
	long double		z_re;
	long double		z_im;
	long double		z_re2;
	long double		z_im2;
	int				x;
	int				y;
	long double		z;
	long double		temp;
	unsigned int	n;
	long double		range;
	long double		rangeim;
	int				arr[256];
	int				color;
	bool			isinside;
	int				ac;
	char			**av;
	int				red;
	int				blue;
	int				green;
	double			sign;
	double			res;
	double			res2;
}	t_data;

int		rgb_to_int(int r, int g, int b);
void	img_pix_put(t_img *img, unsigned int x, unsigned int y, int color);
void	ft_initialise(t_data *data);
int		handle_escape(int Keypress, t_data *data);
int		handle_mouse(int button, int x, int y, t_data *data);
void	juliaSet(t_data *data, t_complex c, long double radius, int n);
int		computationsjulia(t_data *data, int radius, t_complex c);
void	render_julia(t_data *data, int radius, t_complex c);
int		compmandel(t_data *data);
void	render_mandelbrot(t_data *data);
void	render_burningship(t_data *data);
void	ft_initarr(t_data *data);
int		render(t_data *data);
double	ft_atof(t_data *data, const char *str);
int		exitfunction(t_data *data);

void	helper1(t_data *data);
void	helper2(t_data *data, t_complex c);
void	helper3(t_data *data);

#endif
