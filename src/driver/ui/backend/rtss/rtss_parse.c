/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:24:01 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/09 23:31:42 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/rtss_lexer.h"
#include <htab.h>
#include <stdio.h>
#include <stdlib.h>

int	rtss_interpreter(int ac, char **av)
{
	char					*str;
	char					**start;
	struct s_rtss_lex_file	lexed_file;
	t_htab					*tab;

	if (ac < 2)
		return (1);
	str = rtss_file_to_buffer(av[1]);
	start = &str;
	if (!str)
		return (1);
	printf("%s\n", str);
	str = rtss_trim_comment(str);
	printf("%s\n", str);
	lexed_file = rtss_lex_file(str);
	free(*start);
	tab = rtss_parse(lexed_file);
	(void)tab;
	return (0);
}
