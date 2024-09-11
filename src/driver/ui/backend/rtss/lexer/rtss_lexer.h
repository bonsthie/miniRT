/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_lexer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:49:38 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/11 16:05:42 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTSS_LEXER_H
# define RTSS_LEXER_H

# include "../rtss.h"
# include <stdbool.h>

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

/* lexer */
char							*rtss_trim_comment(char *file);
struct s_rtss_lex_file			rtss_lex_file(const char *file);
struct s_rtss_lex_class			*rtss_create_class(const char **str);
struct s_rtss_lex_attr			*rtss_parse_attr(char **str);

/* utils */
bool							rtss_is_empty(char *str);
char							*rtss_get_name(const char **str);
char							*rtss_get_attr_name(const char **str);

/* free */
void rtss_free_lex_file(struct s_rtss_lex_file file);

#endif /* RTSS_LEXER_H */
