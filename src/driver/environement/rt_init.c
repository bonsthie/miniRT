#include "../_rt_mlx.h"
#include <libft.h>
#include <mlx.h>
#include <rt_driver.h>
#include <stdio.h>


int	init_error_process(void)
{
	return (rt_error_signal());
}

t_screen	*rt_init(void)
{
	t_screen	*screen;
	int			pid;

	pid = init_error_process();
	if (!pid || pid == -1)
		exit(0);
	screen = malloc(sizeof(t_screen));
	screen->error_pid = pid;
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
	ft_bzero(screen->hooks.hook_function, HOOK_COUNT * sizeof(t_hooks_function));
	ft_bzero(screen->hooks.data, HOOK_COUNT * sizeof(void));
	return (screen);
}
