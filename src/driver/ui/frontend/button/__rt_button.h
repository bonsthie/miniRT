/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __rt_button.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 10:55:02 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/17 19:24:09 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RT_BUTTON
# define __RT_BUTTON

# include "../../backend/rtss/rtss.h"
# include "../../ui.h"

struct						s_rtss_button_settings
{
	uint32_t				width;
	uint32_t				height;

	uint32_t				border_size;
	uint32_t				border_color;

	uint32_t				color;

	t_rtss_margin			margin;
	t_rtss_padding			padding;
	t_rtss_border_radius	border_radius;
};

struct s_rtss_button_settings	rt_get_button_settings(t_button *button);

#endif // __RT_BUTTON
