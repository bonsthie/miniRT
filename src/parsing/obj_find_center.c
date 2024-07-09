#include "rt_mesh_obj.h"

void	find_center(t_object_mesh *object)
{
	size_t	i;
	size_t	size;

	i = 0;
	object->center.v4f = (t_v4f){0, 0, 0, 0};
	size = object->mesh.size_mesh.vertex;
	while (i < size)
	{
		object->center.v4f += object->mesh.vertex_init[i];
		i++;
	}
	object->center.v4f /= (t_v4f){size, size, size, 1};
	// object->center.v4f -= *(t_v4f *)&object->offset.x;
}
