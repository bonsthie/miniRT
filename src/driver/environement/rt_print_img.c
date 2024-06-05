#include "../_rt_mlx.h"
#include "mlx.h"
#include "rt_driver.h"

void rt_print_img_screen(t_img *img, t_screen *screen, unsigned int x, unsigned int y)
{
	int x_tmp;

	x_tmp = x;
	y += RT_UI_TOP_BAR;
	while (y < RT_HEIGHT)
	{
		x = x_tmp;
		while (x < RT_WIDTH - RT_UI_SIDE_BAR)
		{
			mlx_pixel_put(screen->mlx, screen->win, x, y, img->color[y][x]);
			x++;
		}
		y++;
	}

}
