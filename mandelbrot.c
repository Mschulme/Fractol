#include "ft_fractal.h"


void render_mandelbrot(t_data *data)
{
    const double minre = data->minre;
    const double maxre = data->maxre;
    const double minim = data->minim;
    const double maxim = data->maxim;

    const unsigned int width  = data->width;
    const unsigned int height = data->height;
    const unsigned int max_iter = data->maxiterations;
    int *palette = data->palette;

    // Precompute step factors
    const double re_factor = (double)(maxre - minre) / (double)width;
    const double im_factor = (double)(maxim - minim) / (double)height;

    double *re_values = (double *)malloc(width * sizeof(double));
    for (unsigned int x = 0; x < width; ++x)
    {
        re_values[x] = minre + x * re_factor;
    }

    double *im_values = (double *)malloc(height * sizeof(double));
    for (unsigned int y = 0; y < height; ++y)
    {
        im_values[y] = minim + y * im_factor;
    }

    // Allocate a buffer to store final color values for all pixels
    int *color_cache = (int *)malloc(width * height * sizeof(int));
    if (!color_cache || !re_values || !im_values)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        free(color_cache);
        free(re_values);
        free(im_values);
        return;
    }


//#pragma omp parallel for schedule(dynamic)
#pragma omp simd
    for (unsigned int y = 0; y < height; ++y)
    {
        double Ci = im_values[y];
        for (unsigned int x = 0; x < width; ++x)
        {
            double Zr = 0.0, Zi = 0.0;
            double Tr = 0.0, Ti = 0.0;
            double Cr = re_values[x];

            unsigned int i;
            for (i = 0; i < max_iter; ++i)
            {
                Zi = 2.0 * Zr * Zi + Ci;
                Zr = Tr - Ti + Cr;
                Tr = Zr * Zr;
                Ti = Zi * Zi;
                
                if (Tr + Ti > 4.0)
                    break;
            }

            int color_value = palette[i % max_iter];
            color_cache[y * width + x] = color_value;
        }
    }

    img_pix_put(&data->img, width, height, color_cache);

    // Cleanup
    free(color_cache);
    free(re_values);
    free(im_values);
}
