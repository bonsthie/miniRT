#include "../_rt_mlx.h"
#include "mlx.h"
#include "rt_driver.h"

void rt_print_img_screen(t_img *img, t_screen *screen, unsigned int x, unsigned int y)
{
	int x_tmp;

	x_tmp = x;
	while (y < HEIGHT)
	{
		x = x_tmp;
		while (x < WIDTH)
		{
			mlx_pixel_put(screen->connection, screen->window, x, y, img->color[y][x]);
			x++;
		}
		y++;
	}

}
