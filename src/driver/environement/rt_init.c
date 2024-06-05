#include "../_rt_mlx.h"
#include <mlx.h>
#include <rt_driver.h>
#include <libft.h>

t_screen	*rt_init(void)
{
	t_screen	*screen;

	screen = malloc(sizeof(t_screen));
	if (!screen)
		return (NULL);
	screen->mlx = mlx_init();
	if (!screen->mlx)
	{
		free(screen);
		return (NULL);
	}
	screen->win = mlx_new_window(screen->mlx, RT_WIDTH, RT_HEIGHT, RT_WIN_NAME);
	if (!screen->win)
	{
		free(screen);
		mlx_destroy_display(screen->mlx);
		return (NULL);
	}
	screen->button_top = NULL;
	screen->button_side = NULL;
	screen->mouse_x = INT_MIN;
	screen->mouse_y = INT_MIN;
	return (screen);
}
