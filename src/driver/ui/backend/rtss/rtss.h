/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:48:28 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/06 01:32:28 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTSS_H
# define RTSS_H

enum	e_rtss_lex_attr_type
{
	WIDTH,
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
	BORDER,
	BORDER_WIDTH,
	BORDER_COLOR,
	BORDER_RADIUS,
	BORDER_TOP_LEFT_RADIUS,
	BORDER_TOP_RIGHT_RADIUS,
	BORDER_BOTTOM_RIGHT_RADIUS,
	BORDER_BOTTOM_LEFT_RADIUS,
	BACKGROUND_COLOR,
	BACKGROUND_COLOR_HOWEVER,
	BACKGROUND_COLOR_CLIKED,
};

char	*rtss_file_to_buffer(const char *filename);
char	**fuck_norminette(void);

#endif /* RTSS_H */
