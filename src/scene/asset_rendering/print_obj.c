/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:32:24 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/07 13:23:34 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_mesh_obj.h>
#include <rt_driver.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

t_v4f	cross_product(t_v4f a, t_v4f b)
{
	t_v4f	result;

	result = (t_v4f){a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0]
		* b[1] - a[1] * b[0], 1.0f};
	return (result);
}

float	magnitude(t_v4f v)
{
	t_v4f	v_mul;

	v_mul = v * v;
	return (sqrt(v_mul[0] + v_mul[1] + v_mul[2]));
}

t_v4f	normalize(t_v4f n)
{
	float	mag;
	t_v4f	vmag;

	mag = magnitude(n);
	vmag = (t_v4f){mag, mag, mag, 1};
	return (n / vmag);
}

t_v4f	is_visible(int size, t_point *point, t_mesh mesh)
{
	t_v4f	ab;
	t_v4f	ca;
	t_v4f	n;
	t_v4f	a;
	t_v4f	b;
	t_v4f	c;

	if (size < 3)
		return ((t_v4f){0});
	a = mesh.vertex[point[0].vertex].v4f;
	b = mesh.vertex[point[1].vertex].v4f;
	c = mesh.vertex[point[2].vertex].v4f;
	ab = b - a;
	ca = c - a;
	n = cross_product(ab, ca);
	n = normalize(n) * (t_v4f){0, 0, -1, 1};
	return (n);
}

void	print_face(t_face face, t_mesh mesh, t_img *img)
{
	t_v4f	normal;
	t_v4f	light_dir;
	t_rt_render_info info[4];

	normal = is_visible(face.count, face.point, mesh);
	if (normal[2] <= 0.0f)
		return ;


	light_dir = normalize((t_v4f){0.0f, 0.0f, 1.0f});
	t_v4f dot = normal * light_dir;
	float intensity = fmax(0.0f, dot[0] + dot[1] + dot[2]);
	/* unsigned int grey_value = (unsigned int)(intensity * 255); */
	unsigned int red = (unsigned int)(240 * intensity);
	unsigned int green = (unsigned int)(168 * intensity);
	unsigned int blue = (unsigned int)(53 * intensity);

	// Combine into a single ARGB value
	unsigned int color = 0xFF000000 | (red << 16) | (green << 8) | blue;

	info[0].vector = mesh.vertex[face.point[0].vertex].vec3;
	info[1].vector = mesh.vertex[face.point[1].vertex].vec3;
	info[2].vector = mesh.vertex[face.point[2].vertex].vec3;

	if (face.count == 3)
		display_triangle_rast(info, img, color);
	info[3].vector = mesh.vertex[face.point[3].vertex].vec3;
	if (face.count == 4)
		display_quad_rast(info, img, color);
}

void	print_obj_to_image(t_object_mesh *object, t_img *img)
{
	long	seconds;
	long	ns;
	double	elapsed;

	struct timespec start, end;
	/* printf("start"); */
	clock_gettime(CLOCK_MONOTONIC, &start);
	//#pragma omp parallel for
	for (size_t i = 0 ;i < object->mesh.size_mesh.face; i++)
	{
		print_face(object->mesh.face[i], object->mesh, img);
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	seconds = end.tv_sec - start.tv_sec;
	ns = end.tv_nsec - start.tv_nsec;
	elapsed = seconds + ns * 1e-9;
	(void)elapsed;
	printf("time = %f\n", elapsed);
}
