/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:32:24 by babonnet          #+#    #+#             */
/*   Updated: 2024/05/27 16:19:14 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh_obj.h"
#include "mlx.h"
#include "print_int.h"
#include "mlx_data.h"
#include <math.h>
#include <stdio.h>
#include <time.h>

void print_quad(t_point *point, t_mesh mesh, t_mlx *mlx)
{
	plot_line(mlx, mesh.vertex[point[0].vertex].v4f, mesh.vertex[point[1].vertex].v4f, 0xFFFFFFFF);
	plot_line(mlx, mesh.vertex[point[0].vertex].v4f, mesh.vertex[point[2].vertex].v4f, 0xFFFFFFFF);
	plot_line(mlx, mesh.vertex[point[1].vertex].v4f, mesh.vertex[point[2].vertex].v4f, 0xFFFFFFFF);
	plot_line(mlx, mesh.vertex[point[2].vertex].v4f, mesh.vertex[point[3].vertex].v4f, 0xFFFFFFFF);
	plot_line(mlx, mesh.vertex[point[0].vertex].v4f, mesh.vertex[point[3].vertex].v4f, 0xFFFFFFFF);
}


void print_triangle(t_point *point, t_mesh mesh, t_mlx *mlx)
{
	plot_line(mlx, mesh.vertex[point[0].vertex].v4f, mesh.vertex[point[1].vertex].v4f, 0xFFFFFFFF);
	plot_line(mlx, mesh.vertex[point[0].vertex].v4f, mesh.vertex[point[2].vertex].v4f, 0xFFFFFFFF);
	plot_line(mlx, mesh.vertex[point[1].vertex].v4f, mesh.vertex[point[2].vertex].v4f, 0xFFFFFFFF);
}


t_v4f cross_product(t_v4f a, t_v4f b) {
	t_v4f result;

	result = (t_v4f){
		a[1] * b[2] - a[2] * b[1],
		a[2] * b[0] - a[0] * b[2],
		a[0] * b[1] - a[1] * b[0],
		1.0f
	};
	return result;
}

float magnitude(t_v4f v)
{
	t_v4f v_mul;

	v_mul = v * v;
	return (sqrt(v_mul[0] + v_mul[1] + v_mul[2]));
}

t_v4f normalize(t_v4f n)
{
	float mag;
	t_v4f vmag;

	mag = magnitude(n);
	vmag = (t_v4f ){mag, mag, mag, 1};
	return (n / vmag);
}


int is_visible(int size, t_point *point, t_mesh mesh)
{
	t_v4f ab;
	t_v4f ca;
	t_v4f n;

	if (size < 3)
		return (1);
	t_v4f a =  mesh.vertex[point[0].vertex].v4f;
	t_v4f b =  mesh.vertex[point[1].vertex].v4f;
	t_v4f c =  mesh.vertex[point[2].vertex].v4f;
	ab = b - a;
	ca = c - a;
	n = cross_product(ab, ca);
	n = normalize(n) * (t_v4f){0, 0, -1, 1};
	if (n[2] <= 0.0f)
		return (0);
	return (1);
}

void print_face(t_face face, t_mesh mesh, t_mlx *mlx)
{
	if (!is_visible(face.count, face.point, mesh)) {
		return ;
	}
	if (face.count == 3)
		rast_tri(face.point, mesh, mlx);
	if (face.count == 4)
		print_quad(face.point, mesh, mlx);
}


void print_obj(t_object_mesh *object, t_mlx *mlx)
{
    size_t i;
    struct timespec start, end;

    i = 0;
    clock_gettime(CLOCK_MONOTONIC, &start);
	mlx_clear_window(mlx->connection, mlx->window);
    while (i < object->mesh.size_mesh.face)
    {
        print_face(object->mesh.face[i], object->mesh, mlx);
        i++;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    long seconds = end.tv_sec - start.tv_sec;
    long ns = end.tv_nsec - start.tv_nsec;

    double elapsed = seconds + ns*1e-9;
    printf("time = %f\n", elapsed);
}

