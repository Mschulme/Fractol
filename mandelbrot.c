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


#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846

typedef struct {
    float l;
    float c;
    float h;
} LCH;

typedef struct {
    int r;
    int g;
    int b;
} RGB;

RGB lch_to_rgb(LCH lch)
{
    float rad_h = lch.h * PI / 180.0;
    float a = lch.c * cos(rad_h);
    float b = lch.c * sin(rad_h);

    // Convert LCH to LAB
    float l = lch.l;

    // Convert LAB to XYZ
    float y = (l + 16.0) / 116.0;
    float x = a / 500.0 + y;
    float z = y - b / 200.0;

    x = (x > 0.206893034) ? pow(x, 3) : (x - 16.0 / 116.0) / 7.787;
    y = (y > 0.206893034) ? pow(y, 3) : (y - 16.0 / 116.0) / 7.787;
    z = (z > 0.206893034) ? pow(z, 3) : (z - 16.0 / 116.0) / 7.787;

    x *= 0.95047;
    z *= 1.08883;

    // Convert XYZ to RGB
    float r = x * 3.2406 + y * -1.5372 + z * -0.4986;
    float g = x * -0.9689 + y * 1.8758 + z * 0.0415;
    b = x * 0.0557 + y * -0.2040 + z * 1.0570;

    r = (r > 0.0031308) ? 1.055 * pow(r, 1 / 2.4) - 0.055 : 12.92 * r;
    g = (g > 0.0031308) ? 1.055 * pow(g, 1 / 2.4) - 0.055 : 12.92 * g;
    b = (b > 0.0031308) ? 1.055 * pow(b, 1 / 2.4) - 0.055 : 12.92 * b;

    RGB rgb;
    rgb.r = (int)(fmax(0, fmin(1, r)) * 255);
    rgb.g = (int)(fmax(0, fmin(1, g)) * 255);
    rgb.b = (int)(fmax(0, fmin(1, b)) * 255);

    return rgb;
}

int get_color(int iters, int max_i)
{
    float s = (float)iters / max_i;
    float v = 1.0 - powf(cos(PI * s), 2.0);
    LCH lch;
    lch.l = 75 - (75 * v);
    lch.c = 28 + (75 - (75 * v));
    lch.h = fmod(powf(360 * s, 1.5), 360);

    RGB rgb = lch_to_rgb(lch);
    return (rgb.r << 16) | (rgb.g << 8) | rgb.b;
}

void render_mandelbrot(t_data *data)
{

    data->re_factor = (data->maxre - data->minre) / (data->width - 1);
    data->im_factor = (data->maxim - data->minim) / (data->height - 1);

    for (data->y = 0; data->y < data->height; data->y++)
    {
        data->c_im = data->maxim - data->y * data->im_factor;
        for (data->x = 0; data->x < data->width; data->x++)
        {
            data->c_re = data->minre + data->x * data->re_factor;
            data->z_re = data->c_re;
            data->z_im = data->c_im;
            data->isinside = true;
            data->n = 0;

            double z_re2, z_im2;
            while (data->n < data->maxiterations)
            {
                z_re2 = data->z_re * data->z_re;
                z_im2 = data->z_im * data->z_im;
                if (z_re2 + z_im2 > 4)
                {
                    data->isinside = false;
                    data->color = get_color(data->n, data->maxiterations);
                    img_pix_put(&data->img, data->x, data->y, data->color);
                    break;
                }
                data->z_im = 2 * data->z_re * data->z_im + data->c_im;
                data->z_re = z_re2 - z_im2 + data->c_re;
                data->n++;
            }
            if (data->isinside)
                img_pix_put(&data->img, data->x, data->y, 0x000000);
        }
    }
}
