/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_lexer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:49:38 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/06 01:03:59 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTSS_LEXER_H
# define RTSS_LEXER_H

# include <stdbool.h>

#include "../rtss.h"

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

char							*rtss_trim_comment(char *file);
struct s_rtss_lex_file			rtss_lex_file(const char *file);
struct s_rtss_lex_class			*rtss_create_class(const char **str);
struct s_rtss_lex_attr			*rtss_parse_attr(char **str);

bool							rtss_is_empty(char *str);
char							*rtss_get_name(const char **str);
char							*rtss_get_attr_name(const char **str);

#endif /* RTSS_LEXER_H */
