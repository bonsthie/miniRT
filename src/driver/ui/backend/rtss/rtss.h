/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:48:28 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/10 15:57:56 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTSS_H
# define RTSS_H

# include <htab.h>

enum	e_rtss_lex_attr_type
{
	WIDTH = 0,
	HEIGHT = 1,
	PADDING = 2,
	PADDING_LEFT = 3,
	PADDING_RIGHT = 4,
	PADDING_BOTTOM = 5,
	PADDING_TOP = 6,
	MARGIN = 7,
	MARGIN_LEFT = 8,
	MARGIN_RIGHT = 9,
	MARGIN_BOTTOM = 10,
	MARGIN_TOP = 11,
	BORDER_RADIUS = 12,
	BORDER_TOP_LEFT_RADIUS = 13,
	BORDER_TOP_RIGHT_RADIUS = 14,
	BORDER_BOTTOM_RIGHT_RADIUS = 15,
	BORDER_BOTTOM_LEFT_RADIUS = 16,
	BACKGROUND_COLOR = 17,
	BACKGROUND_COLOR_HOWEVER = 18,
	BACKGROUND_COLOR_CLIKED = 19,
	NULL_ARG = 20,
};

char	*rtss_file_to_buffer(const char *filename);
char	**fuck_norminette(void);
void	**rtss_parser_function(void);

struct s_rtss_lex_file;

t_htab	*rtss_parse(struct s_rtss_lex_file file);

#endif /* RTSS_H */
