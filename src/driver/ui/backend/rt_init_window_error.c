/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init_window_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:09:09 by babonnet          #+#    #+#             */
/*   Updated: 2024/09/05 15:39:12 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ui.h"
#include <signal.h>

#if RT_ERROR_WINDOW

int	*rt_get_error_pid(void)
{
	static int	pid = 0;

	return (&pid);
}

int	init_error_process(void)
{
	return (rt_error_signal());
}

void	__attribute__((constructor)) rt_init_error_window(void)
{
	int	*pid;

	pid = rt_get_error_pid();
	*pid = init_error_process();
	if (!*pid || *pid == -1)
	{
		ft_printf("rt error: fail to start rt error window\n");
		exit(1);
	}
}

void	__attribute__((destructor())) rt_destroy_error_window(void)
{
	kill(*rt_get_error_pid(), SIGTERM);
}

#endif
