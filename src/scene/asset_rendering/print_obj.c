/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:32:24 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/21 18:22:07 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <rt_driver.h>
#include <rt_math.h>
#include <rt_mesh_obj.h>
#include <stdint.h>
#include <time.h>

t_v4f	is_visible(int size, t_point *point, t_mesh mesh)
{
	t_v4f	ab;
	t_v4f	ca;
	t_v4f	n;

	if (size < 3)
		return ((t_v4f){0});
	ab = mesh.vertex[point[1].vertex].v4f - mesh.vertex[point[0].vertex].v4f;
	ca = mesh.vertex[point[2].vertex].v4f - mesh.vertex[point[0].vertex].v4f;
	n = cross_product(ab, ca);
	n = normalize(n) * (t_v4f){0, 0, -1, 1};
	return (n);
}

void	print_face(t_face face, t_mesh mesh, t_img *img, int id)
{
	t_v4f				normal;
	t_v4f				light_dir;
	union u_color		color;
	t_rt_render_info	info[4];
	t_v4f				dot;
	float				intensity;

	normal = is_visible(face.count, face.point, mesh);
	if (normal[2] <= 0.0f)
		return ;
	light_dir = normalize((t_v4f){0.0f, 0.0f, 1.0f});
	dot = normal * light_dir;
	intensity = fmax(0.0f, dot[0] + dot[1] + dot[2]);
	color.components.alpha = 0xFF;
	color.components.red = (uint8_t)face.color.components.red * intensity;
	color.components.green = (uint8_t)face.color.components.green * intensity;
	color.components.blue = (uint8_t)face.color.components.blue * intensity;
	info[0].vector = mesh.vertex[face.point[0].vertex].vec3;
	info[1].vector = mesh.vertex[face.point[1].vertex].vec3;
	info[2].vector = mesh.vertex[face.point[2].vertex].vec3;
	if (face.count == 3)
		rt_display_triangle_rast(info, img, color.value, id);
	info[3].vector = mesh.vertex[face.point[3].vertex].vec3;
	if (face.count == 4)
		rt_display_quad_rast(info, img, color.value, id);
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
		print_face(object->mesh.face[i], object->mesh, img, id);
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	seconds = end.tv_sec - start.tv_sec;
	ns = end.tv_nsec - start.tv_nsec;
	elapsed = seconds + ns * 1e-9;
	(void)elapsed;
	/* printf("time = %f\n", elapsed); */
}
