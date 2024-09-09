/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __rtss_type.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:30:21 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/09 20:16:26 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RTSS_TYPE_H
# define __RTSS_TYPE_H

# include <stdint.h>

uint64_t	__rtss_type_color(char *value);

uint64_t	__rtss_bit_packing_1(char **value, uint64_t nb);
uint64_t	__rtss_bit_packing_2(char **value, uint64_t nb);
uint64_t	__rtss_bit_packing_3(char **value, uint64_t nb);
uint64_t	__rtss_bit_packing_4(char **value, uint64_t nb);
uint64_t	__rtss_bit_packing(char **value);

#endif /* __RTSS_TYPE_H */
