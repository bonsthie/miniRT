/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_type_utils_bit_packing.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:39:36 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/17 14:46:34 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdint.h>

uint64_t	__rtss_bit_packing_1(char **value, uint64_t nb)
{
	nb &= (~0ULL >> 16) << 16;
	nb |= (ft_strtoll(*value, value, 10) & 0xFFFF);
	return (nb);
}

uint64_t	__rtss_bit_packing_2(char **value, uint64_t nb)
{
	nb &= ~(0xFFFFULL << 16);
	nb |= (ft_strtoll(*value, value, 10) & 0xFFFF) << 16;
	return (nb);
}

uint64_t	__rtss_bit_packing_3(char **value, uint64_t nb)
{
	nb &= ~(0xFFFFULL << 32);
	nb |= (ft_strtoll(*value, value, 10) & 0xFFFF) << 32;
	return (nb);
}

uint64_t	__rtss_bit_packing_4(char **value, uint64_t nb)
{
	nb &= ~(0xFFFFULL << 48);
	nb |= (ft_strtoll(*value, value, 10) & 0xFFFF) << 48;
	return (nb);
}

uint64_t	__rtss_bit_packing(char **value)
{
	char		**split_args;
	uint16_t	args[4];
	int			i;

	split_args = ft_split(*value, ' ');
	if (!split_args)
		return (((uint64_t) - 1) / UINT16_MAX * (uint16_t)ft_atoi(*value));
	i = -1;
	while (split_args[++i] && i < 4)
		args[i] = ft_atoi(split_args[i]);
	free_strs(split_args);
	if (i == 1)
		return (((uint64_t) - 1) / UINT16_MAX * args[0]);
	else if (i == 2)
	{
		return ((((uint64_t) - 1) / UINT32_MAX * args[0])
			| ((((uint64_t) - 1) / UINT32_MAX * args[1]) << 16));
	}
	else if (i == 3)
		args[3] = args[1];
	return (((uint64_t)(args[0])) << 48
	| ((uint64_t)(args[1])) << 32
	| ((uint64_t)(args[2])) << 16
	| ((uint64_t)(args[3])));
}
