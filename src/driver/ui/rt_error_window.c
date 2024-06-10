/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error_window.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:13:18 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/09 18:42:57 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "../_rt_mlx.h"

#if RT_ERROR_WINDOW

void rt_error_window(t_screen *screen, const char *error_msg)
{
	union sigval sv;
	sv.sival_ptr = (void *)error_msg;
	sigqueue(screen->error_pid, SIGUSR1, sv);
}

#else

void rt_error_window(t_screen *screen, const char *error_msg)
{
	ft_printf(error_msg);
	(void)screen;
}

#endif

