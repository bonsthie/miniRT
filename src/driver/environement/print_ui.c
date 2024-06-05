#include "../_rt_mlx.h"
#include "mlx.h"
#include "rt_driver.h"


void rt_print_ui_screen(t_screen *screen)
{
	int x;
	int y;

	y = RT_UI_TOP_BAR;
	while (y < RT_HEIGHT)
	{
		x = RT_WIDTH - RT_UI_SIDE_BAR;
		while (x < RT_WIDTH)
		{
			mlx_pixel_put(screen->connection, screen->window, x, y, RT_UI_SIDE_BAR_COLOR);
			x++;
		}
		y++;
	}
	y = 0;
	while (y < RT_UI_TOP_BAR)
	{
		x = 0;
		while (x < RT_WIDTH)
		{
			mlx_pixel_put(screen->connection, screen->window, x, y, RT_UI_TOP_BAR_COLOR);
			x++;
		}
		y++;
	}
}
