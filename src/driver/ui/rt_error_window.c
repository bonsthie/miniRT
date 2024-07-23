/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error_window.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:13:18 by babonnet          #+#    #+#             */
/*   Updated: 2024/07/23 13:27:24 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "../_rt_mlx.h"

#if RT_ERROR_WINDOW

void rt_error_window(const char *error_msg)
{
	if (!error_msg)
		return ;
	union sigval sv;
	sv.sival_ptr = (void *)error_msg;
	sigqueue(*rt_get_error_pid(), SIGUSR1, sv);
}

#else

void rt_error_window(const char *error_msg)
{
	if (!error_msg)
		return ;
	ft_printf("%s\n", error_msg);
}

#endif

