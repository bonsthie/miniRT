#include "../_rt_mlx.h"
#include <mlx.h>
#include <rt_driver.h>
#include <libft.h>
#include <signal.h>
#include <stdio.h>
#include "hook/_hook.h"




void error_handler(int sig) {
	void *win;
	void  *mlx;
	int pid;

    if (sig == SIGUSR1) {
		pid = fork();
		if (pid)
			return ;
		mlx = mlx_init();
		win = mlx_new_window(mlx, 100, 200, "Error");
		mlx_on_event(mlx, win, MLX_WINDOW_EVENT, window_hook, mlx);
		mlx_loop(mlx);
		mlx_destroy_window(mlx, win);
		mlx_destroy_display(mlx);
    }
}

int init_error_process(void)
{
	int pid;
	/* void *mlx; */

	pid = fork();
	if (pid)
		return (pid);
	signal(SIGUSR1, error_handler);
	while(1)
	{
		pause();
	}
	
}

t_screen	*rt_init(void)
{
	t_screen	*screen;

	int pid = init_error_process();
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
	return (screen);
}
