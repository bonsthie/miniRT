/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:24:01 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/04 18:37:29 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtss_lexer.h"
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	if (ac < 2)
		return (1);
	char *str = rtss_file_to_buffer(av[1]);
	if (!str)
		return (1);
	printf("%s\n", str);
	str = rtss_trim_comment(str);
	printf("%s\n", str);
	rtss_lex_file(str);
	/* free(str); */
}
