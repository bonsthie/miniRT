/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_parse.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:51:52 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/09 17:00:49 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTSS_PARSE_H
#define RTSS_PARSE_H

#include "../lexer/rtss_lexer.h"

typedef void t_rtss_parse_func(t_htab *tab, t_hentry *entry, char *value);

void rtss_attr_to_hentry_spec(struct s_rtss_lex_attr *attr, t_htab *tab, t_hentry *entry);
void rtss_class_to_hentry(t_htab *tab, struct s_rtss_lex_class *class);

#endif /* RTSS_PARSE_H */
