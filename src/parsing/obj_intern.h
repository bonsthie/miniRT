/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intern.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:39:58 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/19 16:24:36 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_INTERN_H
# define OBJ_INTERN_H

# include "libft.h"
# include <rt_mesh_obj.h>

void	free_mesh(t_mesh *mesh);
int		alloc_mesh(t_mesh *mesh);

#endif
