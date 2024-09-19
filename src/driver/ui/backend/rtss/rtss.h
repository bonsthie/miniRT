/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:48:28 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/19 15:34:57 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTSS_H
# define RTSS_H

#include "htab.h"
#include <stdint.h>

enum	e_rtss_lex_attr_type
{
	WIDTH = 1,
	HEIGHT,
	PADDING,
	PADDING_LEFT,
	PADDING_RIGHT,
	PADDING_BOTTOM,
	PADDING_TOP,
	MARGIN,
	MARGIN_LEFT,
	MARGIN_RIGHT,
	MARGIN_BOTTOM,
	MARGIN_TOP,
	BORDER_RADIUS,
	BORDER_TOP_LEFT_RADIUS,
	BORDER_TOP_RIGHT_RADIUS,
	BORDER_BOTTOM_RIGHT_RADIUS,
	BORDER_BOTTOM_LEFT_RADIUS,
	BACKGROUND_COLOR,
	BACKGROUND_COLOR_HOWEVER,
	BACKGROUND_COLOR_CLIKED,
	BORDER_SIZE,
	BORDER_COLOR,
	NULL_ARG,
};

typedef union u_rtss_margin
{
	uint64_t	data;
	struct {
		uint16_t	left;
		uint16_t	bottom;
		uint16_t	right;
		uint16_t	top;
	};
} t_rtss_margin;

typedef union u_rtss_padding
{
	uint64_t	data;
	struct {
		uint16_t	left;
		uint16_t	bottom;
		uint16_t	right;
		uint16_t	top;
	};
} t_rtss_padding;

typedef union u_rtss_border_radius
{
	uint64_t	data;
	struct {
		uint16_t	top_left;
		uint16_t	top_right;
		uint16_t	bottom_right;
		uint16_t	bottom_left;
	};
} t_rtss_border_radius;

t_htab	*rtss_interpreter(const char *file);

#endif /* RTSS_H */
