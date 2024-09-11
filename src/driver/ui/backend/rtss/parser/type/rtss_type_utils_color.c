/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_type_utils_color.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:29:38 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/10 15:57:56 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>
#include <stdio.h>

uint64_t	__rtss_type_color(char *value)
{
	char		*start_number;
	uint64_t	num;

	start_number = ft_strchr(value, '#');
	if (start_number)
		num = ft_strtoll(start_number + 1, NULL, 16);
	else
		num = ft_strtoll(value, NULL, 0);
	return (num);
}
