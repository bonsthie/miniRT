#include "rt_driver.h"
#include "rt_mesh_obj.h"

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
	// object->center.v4f -= *(t_v4f *)&object->offset.x;
}
