/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:32:24 by babonnet          #+#    #+#             */
/*   Updated: 2024/07/21 23:51:34 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>
#include <rt_driver.h>
#include <rt_math.h>
#include <rt_mesh_obj.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

t_v4f	is_visible(t_rt_render_info *info)
{
	t_v4f	ab;
	t_v4f	ca;
	t_v4f	n;

	if (info->count < 3)
		return ((t_v4f){0});
	ab = info->vertex[1].v4f - info->vertex[0].v4f;
	ca = info->vertex[2].v4f - info->vertex[0].v4f;
	n = cross_product(ab, ca);
	n = normalize(n) * (t_v4f){0, 0, -1, 1};
	return (n);
}


t_rt_render_info extract_tri_info_from_face(t_face face, t_mesh mesh)
{
	t_rt_render_info	info;

	info.vertex[0] = mesh.vertex[face.point[0].vertex];
	info.vertex[1] = mesh.vertex[face.point[1].vertex];
	info.vertex[2] = mesh.vertex[face.point[2].vertex];
	if (face.count == 4)
		info.vertex[3] = mesh.vertex[face.point[3].vertex];
	info.color = face.color;
	info.count = face.count;
	return (info);
}

void	print_face(t_rt_render_info info, t_img *img, int id)
{
	t_v4f				normal;
	t_v4f				light_dir;
	t_v4f				dot;
	float				intensity;

	normal = is_visible(&info);
	if (normal[2] <= 0.0f)
		return ;
	light_dir = normalize((t_v4f){0.0f, 0.0f, 1.0f});
	dot = normal * light_dir;
	intensity = fmax(0.0f, dot[0] + dot[1] + dot[2]);

	info.color.components.alpha = 0xFF;
	info.color.components.red = (uint8_t)info.color.components.red * intensity;
	info.color.components.green = (uint8_t)info.color.components.green * intensity;
	info.color.components.blue = (uint8_t)info.color.components.blue * intensity;

	if (info.count == 3)
		rt_display_triangle_rast(&info, img, id);
	if (info.count == 4)
		rt_display_quad_rast(&info, img, id);
}

void	print_obj_to_image(t_object_mesh *object, t_img *img, int id)
{
	long	seconds;
	long	ns;
	double	elapsed;

	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
#pragma omp parallel for
	for (size_t i = 0; i < object->mesh.size_mesh.face; i++)
	{
		print_face(extract_tri_info_from_face(object->mesh.face[i], object->mesh), img, id);
	}
	for (int i = 0; i < 10; i++) 
	{
		for  (int y = 0; y < 10; y++)
			rt_put_pixel_img_protected(img, object->relative_center.vec3.x + i, object->relative_center.vec3.y + y, SHORT_MIN, 0xFFFF0000);
	}
	for (int i = 0; i < 10; i++) 
	{
		for  (int y = 0; y < 10; y++)
			rt_put_pixel_img_protected(img, object->relative_point.vec3.x + i, object->relative_point.vec3.y + y, SHORT_MIN, 0xFF00FF00);
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	seconds = end.tv_sec - start.tv_sec;
	ns = end.tv_nsec - start.tv_nsec;
	elapsed = seconds + ns * 1e-9;
	(void)elapsed;
	/* printf("time = %f\n", elapsed); */
}

void	print_obj_to_image_color(t_object_mesh *object, t_img *img, int id, unsigned int color)
{
	long	seconds;
	long	ns;
	double	elapsed;

	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
#pragma omp parallel for
	for (size_t i = 0; i < object->mesh.size_mesh.face; i++)
	{
		t_rt_render_info info = extract_tri_info_from_face(object->mesh.face[i], object->mesh);
		info.color.value = color;
		print_face(info , img, id);
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	seconds = end.tv_sec - start.tv_sec;
	ns = end.tv_nsec - start.tv_nsec;
	elapsed = seconds + ns * 1e-9;
	(void)elapsed;
	/* printf("time = %f\n", elapsed); */
}
