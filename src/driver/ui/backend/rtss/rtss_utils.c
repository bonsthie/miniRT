/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 01:02:16 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/06 01:20:31 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	**fuck_norminette(void)
{
	static char	*norminette_is_a_slut[] = (char *[]){"width", "height",
			"min-width", "max-width", "min-height", "max-height", "padding",
			"padding-left", "padding-right", "padding-bottom", "padding-top",
			"margin", "margin-left", "margin-right", "margin-bottom",
			"margin-top", "border", "border-width", "border-color",
			"border-radius", "border-top-left-radius",
			"border-top-right-radius", "border-bottom-right-radius",
			"border-bottom-left-radius", "background-color",
			"background-color-however", "background-color-clicked", NULL};

	return (norminette_is_a_slut);
}
void func(void)
{
	return ;
}

void **rtss_parser_function(void)
{
	return ((void *[]){
		func,
		func,
		func,
		func,
		NULL
	});
}
