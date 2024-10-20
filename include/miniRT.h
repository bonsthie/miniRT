/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:05:42 by babonnet          #+#    #+#             */
/*   Updated: 2024/10/18 16:27:16 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "htab.h"
# include "rt_driver.h"
# include <stdint.h>

typedef struct s_scene	t_scene;

struct					s_hook_data
{
	t_img				*img;
	t_screen			*screen;
	t_scene				*scene;
};

// Enum to distinguish between different file types supported by the engine.
typedef enum e_file_type
{
	OBJECT_OBJ = 0,
	OBJECT_SPHERE,
	OBJECT_CUBE,
	OBJECT_PLANE,
	OBJECT_CYLINDER,
}						t_file_type;

t_htab	*rtss_interpreter(const char *file);

#endif
