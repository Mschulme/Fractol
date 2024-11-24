#include "ft_fractal.h"

void render_mandelbrot(t_data *data)
{
    int iter = data->maxiterations;
    int iter_x, iter_y;

    long double Zr, Zi, Cr, Ci, Tr, Ti;

    int width = data->width;
    int height = data->height;
    long double minre = data->minre;
    long double maxre = data->maxre;
    long double minim = data->minim;
    long double maxim = data->maxim;
    RGB *palette = data->palette;

    long double re_factor = (maxre - minre) / width;
    long double im_factor = (maxim - minim) / height;

    int *color_cache = (int *)malloc(width * height * sizeof(int));

    #pragma omp parallel for private(iter_x, Zr, Zi, Cr, Ci, Tr, Ti) schedule(dynamic)
    for (iter_y = 0; iter_y < height; ++iter_y)
    {
        for (iter_x = 0; iter_x < width; ++iter_x)
        {
            Zr = Zi = Tr = Ti = 0.0;
            Cr = minre + iter_x * re_factor;
            Ci = minim + iter_y * im_factor;

            int i;
            for (i = 0; i < iter && (Tr + Ti <= 4.0); ++i)
            {
                Zi = 2.0 * Zr * Zi + Ci;
                Zr = Tr - Ti + Cr;
                Tr = Zr * Zr;
                Ti = Zi * Zi;
            }
            RGB color = palette[i % iter];
            int color_value = (color.r << 16) | (color.g << 8) | color.b;
            color_cache[iter_y * width + iter_x] = color_value;
        }
    }
    img_pix_put(&data->img, width, height, color_cache);
    free(color_cache);
}
