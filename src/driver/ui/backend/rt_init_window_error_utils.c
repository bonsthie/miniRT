/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init_window_error_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:47:23 by babonnet          #+#    #+#             */
/*   Updated: 2024/09/05 15:40:24 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../environement/hook/_hook.h"
#include <mlx.h>
#include <signal.h>

#if RT_ERROR_WINDOW

void	*print_error(void *mlx, void *win, char *shared_message)
{
	void	*img;

	img = mlx_png_file_to_image(mlx, "asset/error_window.png", NULL, NULL);
	if (img)
		mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_string_put(mlx, win, 80, 75, 0xFFFFFFFF, shared_message);
	return (img);
}

int	_button_click(int key, void *data)
{
	int	x;
	int	y;

	if (key == MOUSE_LEFT)
	{
		mlx_mouse_get_pos(data, &x, &y);
		if (x >= 381 && y >= 147 && x <= 432 && y <= 172)
			mlx_loop_end(data);
	}
	return (0);
}

void	error_handler(int __sig, siginfo_t *__si, void *__unused)
{
	void	*win;
	void	*mlx;
	void	*img;
	int		pid;
	char	*shared_message;

	if (__sig == SIGUSR1)
	{
		pid = fork();
		if (pid)
			return ;
		shared_message = (char *)__si->si_value.sival_ptr;
		mlx = mlx_init();
		win = mlx_new_window(mlx, 450, 180, "Error");
		mlx_on_event(mlx, win, MLX_WINDOW_EVENT, rt_window_hook, mlx);
		img = print_error(mlx, win, shared_message);
		mlx_on_event(mlx, win, MLX_MOUSEDOWN, _button_click, mlx);
		mlx_loop(mlx);
		mlx_destroy_window(mlx, win);
		if (img)
			mlx_destroy_image(mlx, img);
		mlx_destroy_display(mlx);
		exit(0);
	}
	(void)__unused;
}

int	rt_error_signal(void)
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
		exit(1);
	while (1)
	{
		pause();
	}
	return (0);
}

#else

int	rt_error_signal(void)
{
	return (-2);
}

#endif
