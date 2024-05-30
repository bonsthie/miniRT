/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rast_tri.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:29:06 by babonnet          #+#    #+#             */
/*   Updated: 2024/05/30 19:24:48 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mesh_obj.h"
#include "miniRT.h"
#include "mlx.h"
#include "mlx_data.h"
#include "print_int.h"

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


t_tri mesh_to_triangle(t_mesh mesh, t_point point[3])
{
	t_tri triangle;

	triangle.vertex1.position = mesh.vertex[point[0].vertex].vec3;
	triangle.vertex2.position = mesh.vertex[point[1].vertex].vec3;
	triangle.vertex3.position = mesh.vertex[point[2].vertex].vec3;
	return (triangle);
}

void rast_tri(t_tri triangle, t_mlx *mlx, unsigned int color, int zbuffer[WIDTH][HEIGHT]) 
{
	// bounding box
	int min_x = min(triangle.vertex1.position.x, min(triangle.vertex2.position.x, triangle.vertex3.position.x));
	int min_y = min(triangle.vertex1.position.y, min(triangle.vertex2.position.y, triangle.vertex3.position.y));
	int max_x = max(triangle.vertex1.position.x, max(triangle.vertex2.position.x, triangle.vertex3.position.x));
	int max_y = max(triangle.vertex1.position.y, max(triangle.vertex2.position.y, triangle.vertex3.position.y));

	//edge function coeff
	int A12 = triangle.vertex2.position.y - triangle.vertex1.position.y;
    int A23 = triangle.vertex3.position.y - triangle.vertex2.position.y;
    int A31 = triangle.vertex1.position.y - triangle.vertex3.position.y;
    int B12 = triangle.vertex1.position.x - triangle.vertex2.position.x;
    int B23 = triangle.vertex2.position.x - triangle.vertex3.position.x;
    int B31 = triangle.vertex3.position.x - triangle.vertex1.position.x;

	int y = min_y;
	while (y <= max_y)
	{
		int x = min_x;
		while (x <= max_x)
		{
			// edge function detection
			int w0 = A23 * (x - triangle.vertex2.position.x) + B23 * (y - triangle.vertex2.position.y);
            int w1 = A31 * (x - triangle.vertex3.position.x) + B31 * (y - triangle.vertex3.position.y);
            int w2 = A12 * (x - triangle.vertex1.position.x) + B12 * (y - triangle.vertex1.position.y);
			// is in the triangle
			if (w0 >= -10 && w1 >= -10 && w2 >= -10) 
			{
				if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT && triangle.vertex1.position.z < zbuffer[x][y])
				{
					zbuffer[x][y] = triangle.vertex1.position.z;
					mlx_pixel_put(mlx->connection, mlx->window, x, y, color);
				}
			}
			x++;
		}
		y++;
	}
}
