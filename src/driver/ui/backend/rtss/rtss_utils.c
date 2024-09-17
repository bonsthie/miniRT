/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 01:02:16 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/17 14:01:26 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/type/rtss_type.h"
#include <stdio.h>
#include <stdlib.h>

char	**fuck_norminette(void)
{
	static char	*norminette_is_a_slut[] = (char *[]){"", "width", "height",
		"padding", "padding-left", "padding-right", "padding-bottom",
		"padding-top", "margin", "margin-left", "margin-right",
		"margin-bottom", "margin-top", "border-radius",
		"border-top-left-radius", "border-top-right-radius",
		"border-bottom-right-radius", "border-bottom-left-radius",
		"background-color", "background-color-however",
		"background-color-clicked", NULL};

	return (norminette_is_a_slut);
}

void	**rtss_parser_function(void)
{
	static void *return_func[] = (void *[]){ NULL,
		rtss_type_width, rtss_type_height, rtss_type_padding,
		rtss_type_padding_left, rtss_type_padding_right,
		rtss_type_padding_bottom, rtss_type_padding_top, rtss_type_margin,
		rtss_type_margin_left, rtss_type_margin_right,
		rtss_type_margin_bottom, rtss_type_margin_top,
		rtss_type_border_radius, rtss_type_border_radius_top_left,
		rtss_type_border_radius_top_right,
		rtss_type_border_radius_bottom_right,
		rtss_type_border_radius_bottom_left, rtss_type_background_color,
		rtss_type_background_color_however,
		rtss_type_background_color_click,
	};
	return (return_func);
}
