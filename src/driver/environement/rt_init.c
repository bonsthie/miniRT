#include "../_rt_mlx.h"
#include <libft.h>
#include <mlx.h>

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
		mlx_destroy_display(screen->mlx);
		free(screen);
		return (NULL);
	}
	screen->button_top = NULL;
	screen->button_side = NULL;
	screen->mouse_x = INT_MIN;
	screen->mouse_y = INT_MIN;
	ft_bzero(screen->hooks.hook_function, HOOK_COUNT * sizeof(t_hooks_function));
	ft_bzero(screen->hooks.data, HOOK_COUNT * sizeof(void));
	return (screen);
}
