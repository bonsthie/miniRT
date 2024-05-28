/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rast_tri.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:29:06 by babonnet          #+#    #+#             */
/*   Updated: 2024/05/28 15:41:18 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh_obj.h"
#include "miniRT.h"
#include "mlx.h"
#include "mlx_data.h"

static int min(int p1, int p2)
{
	if (p1 > p2)
		return (p2);
	return (p1);
}

static int max(int p1, int p2)
{
	if (p1 < p2)
		return (p2);
	return (p1);
}

typedef struct s_tri {
	t_vec3 p1;
	t_vec3 p2;
	t_vec3 p3;
} t_tri;

t_tri mesh_to_triangle(t_mesh mesh, t_point point[3])
{
	t_tri triangle;

	triangle.p1 = mesh.vertex[point[0].vertex].vec3;
	triangle.p2 = mesh.vertex[point[1].vertex].vec3;
	triangle.p3 = mesh.vertex[point[2].vertex].vec3;
	return (triangle);
}


void rast_tri(t_point *point, t_mesh mesh, t_mlx *mlx) 
{
	t_tri triangle;

	triangle = mesh_to_triangle(mesh, point);

	// bounding box
	int min_x = min(triangle.p1.x, min(triangle.p2.x, triangle.p3.x));
	int min_y = min(triangle.p1.y, min(triangle.p2.y, triangle.p3.y));
	int max_x = max(triangle.p1.x, max(triangle.p2.x, triangle.p3.x));
	int max_y = max(triangle.p1.y, max(triangle.p2.y, triangle.p3.y));

	//edge function coeff
	int A12 = triangle.p2.y - triangle.p1.y;
    int A23 = triangle.p3.y - triangle.p2.y;
    int A31 = triangle.p1.y - triangle.p3.y;
    int B12 = triangle.p1.x - triangle.p2.x;
    int B23 = triangle.p2.x - triangle.p3.x;
    int B31 = triangle.p3.x - triangle.p1.x;

	int y = min_y - 2;
	while (y <= max_y + 2)
	{
		int x = min_x - 2;
		while (x <= max_x + 2)
		{
			// edge function detection
			int w0 = A23 * (x - triangle.p2.x) + B23 * (y - triangle.p2.y);
            int w1 = A31 * (x - triangle.p3.x) + B31 * (y - triangle.p3.y);
            int w2 = A12 * (x - triangle.p1.x) + B12 * (y - triangle.p1.y);
			// is in the triangle
			if (w0 >= 0 && w1 >= 0 && w2 >= 0) 
			{
				mlx_pixel_put(mlx->connection, mlx->window, x, y, 0xFFFFFFFF);
			}
			x++;
		}
		y++;
	}
}
