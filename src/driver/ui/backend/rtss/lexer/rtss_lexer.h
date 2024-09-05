/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_lexer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:49:38 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/04 23:02:07 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTSS_LEXER_H
# define RTSS_LEXER_H

# include <stdbool.h>
enum							e_rtss_lex_attr_type
{
	WIDTH,
	HEIGHT,
	MIN_WIDTH,
	MAX_WIDTH,
	MIN_HEIGHT,
	MAX_HEIGHT,
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
	BORDER_STYLE,
	BORDER_COLOR,
	BORDER_TOP,
	BORDER_TOP_WIDTH,
	BORDER_TOP_STYLE,
	BORDER_TOP_COLOR,
	BORDER_RIGHT,
	BORDER_RIGHT_WIDTH,
	BORDER_RIGHT_STYLE,
	BORDER_RIGHT_COLOR,
	BORDER_BOTTOM,
	BORDER_BOTTOM_WIDTH,
	BORDER_BOTTOM_STYLE,
	BORDER_BOTTOM_COLOR,
	BORDER_LEFT,
	BORDER_LEFT_WIDTH,
	BORDER_LEFT_COLOR,
	BORDER_RADIUS,
	BORDER_TOP_LEFT_RADIUS,
	BORDER_TOP_RIGHT_RADIUS,
	BORDER_BOTTOM_RIGHT_RADIUS,
	BORDER_BOTTOM_LEFT_RADIUS,
	BACKGROUND_COLOR,
	BACKGROUND_COLOR_HOWEVER,
	BACKGROUND_COLOR_CLIKED,
};

struct							s_rtss_lex_attr
{
	enum e_rtss_lex_attr_type	type;
	char						*value;
	struct s_rtss_lex_attr		*next;
};

struct							s_rtss_lex_class
{
	char						*name;
	struct s_rtss_lex_attr		*attr;
	struct s_rtss_lex_class		*next;
};

struct							s_rtss_lex_file
{
	struct s_rtss_lex_class		*head;
};

char							*rtss_file_to_buffer(const char *filename);
char							*rtss_trim_comment(char *file);
struct s_rtss_lex_file			rtss_lex_file(const char *file);
struct s_rtss_lex_file			rtss_lex_file(const char *file);
struct s_rtss_lex_class			*rtss_create_class(const char **str);
struct s_rtss_lex_attr			*rtss_parse_attr(char **str);

bool							rtss_is_empty(char *str);
char							*rtss_get_name(const char **str);
char							*rtss_get_attr_name(const char **str);
int								is_name_char(int c);
char							**fuck_norminette(void);

#endif /* RTSS_LEXER_H */
