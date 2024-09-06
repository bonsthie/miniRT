/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:24:01 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/06 14:28:10 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/rtss_lexer.h"
#include <stdio.h>
#include <stdlib.h>

int rtss_parse(int ac, char **av)
{
	if (ac < 2)
		return (1);
	char *str = rtss_file_to_buffer(av[1]);
	char **start = &str;
	if (!str)
		return (1);
	printf("%s\n", str);
	str = rtss_trim_comment(str);
	printf("%s\n", str);
	rtss_lex_file(str);
	free(*start);
	return (0);
}
