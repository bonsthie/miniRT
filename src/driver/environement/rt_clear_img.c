#include "../_rt_mlx.h"
#include <libft.h>
#include <limits.h>

void rt_set_image_color(t_img *img, unsigned int color)
{
	int y;
	int x;

	y = 0;
	while (y < RT_HEIGHT)
	{
		x = 0;
		while (x < RT_WIDTH)
		{
			img->zbuffer[y][x] = SHRT_MAX;
			img->color[y][x] = color;
			img->obj_id[y][x] = 0;
			x++;
		}
		y++;
	}
}
