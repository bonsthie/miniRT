/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:18:57 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/13 23:26:11 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// Aligned vector types for optimal hardware utilization by use of avx.
typedef float	__attribute__((aligned(16), vector_size(16))) t_v4f;

// Generic pointer for texture data,
typedef void	t_image;

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
