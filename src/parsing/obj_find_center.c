#include "rt_driver.h"
#include "rt_mesh_obj.h"
#include <stdio.h>

void	find_center(t_object_mesh *object, t_v4f *vertex, t_v4f *center)
{
	size_t	i;
	size_t	size;

	i = 0;
	*center = (t_v4f){0, 0, 0, 0};
	size = object->mesh.size_mesh.vertex;
	while (i < size)
	{
		*center += vertex[i];
		i++;
	}
	*center /= (t_v4f){size, size, size, 1};
}

void	down_center(t_object_mesh *object)
{
	object->saving_point.v4f = object->center.v4f + (t_v4f){100, 0, 0, 0};
	printf("center :%f %f %f\n",
		object->center.v4f[0],
		object->center.v4f[1],
		object->center.v4f[2]
	);
	printf("point:%f %f %f\n",
		object->saving_point.v4f[0],
		object->saving_point.v4f[1],
		object->saving_point.v4f[2]
	);
}
