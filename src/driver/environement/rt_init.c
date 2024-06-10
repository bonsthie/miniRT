#include "../_rt_mlx.h"
#include "hook/_hook.h"
#include <libft.h>
#include <mlx.h>
#include <rt_driver.h>
#include <signal.h>
#include <stdio.h>

#if RT_ERROR_WINDOW

void *print_error(void *mlx, void *win, char *shared_message)
{
	void *img;

	img = mlx_png_file_to_image(mlx, "asset/error_window.png", NULL, NULL);
	if (img)
		mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_string_put(mlx, win, 80, 75, 0xFFFFFFFF, shared_message);
	return (img);
}

int _button_click(int key, void *data)
{
	int x;
	int y;

	if (key == MOUSE_LEFT)
	{
		mlx_mouse_get_pos(data, &x, &y);
		if (x >= 381 && y >= 147 && x <= 432 && y <= 172)
			mlx_loop_end(data);
	}
	return (0);
}

typedef struct s_mlx_data
{
	void	*win;
	void	*mlx;
} t_mlx_data;

void	error_handler(int sig, siginfo_t *si, void *unused)
{
	void	*win;
	void	*mlx;
	void	*img;
	int		pid;
	char	*shared_message;

	if (sig == SIGUSR1)
	{
		pid = fork();
		if (pid)
			return ;
		shared_message = (char *)si->si_value.sival_ptr;
		mlx = mlx_init();
		win = mlx_new_window(mlx, 450, 180, "Error");
		mlx_on_event(mlx, win, MLX_WINDOW_EVENT, window_hook, mlx);
		img = print_error(mlx, win, shared_message);
		mlx_on_event(mlx, win, MLX_MOUSEDOWN, _button_click, mlx);
		mlx_loop(mlx);
		mlx_destroy_window(mlx, win);
		if (img)
			mlx_destroy_image(mlx, img);
		mlx_destroy_display(mlx);
		exit(0);
	}
	(void)unused;
}

int rt_error_signal(void)
{
	int					pid;
	struct sigaction	sa;

	pid = fork();
	if (pid)
		return (pid);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = error_handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(1);
	}
	while (1)
	{
		pause();
	}
	return (0);
}

#else

int rt_error_signal(void) 
{
	return (-2);
}

#endif

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
	return (screen);
}
