/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:05:42 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/19 16:24:36 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdint.h>

union			u_color
{
	int			value;
	struct
	{
		uint8_t	alpha;
		uint8_t	red;
		uint8_t	green;
		uint8_t	blue;
	} components;
};

// Enum to distinguish between different file types supported by the engine.
typedef enum e_file_type
{
	OBJECT_OBJ = 0,
	OBJECT_SPHERE,
	OBJECT_CUBE,
	OBJECT_PLANE,
	OBJECT_CYLINDER,
}				t_file_type;

#endif
