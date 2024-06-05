#include "../_rt_mlx.h"
#include "mlx.h"
#include "rt_driver.h"

t_rt	*rt_init(void)
{
	t_rt	*rt;

	rt = malloc(sizeof(t_rt));
	if (!rt)
		return (NULL);
	rt->mlx = mlx_init();
	if (!rt->mlx)
	{
		free(rt);
		return (NULL);
	}
	rt->win = mlx_new_window(rt->mlx, RT_WIDTH, RT_HEIGHT, RT_WIN_NAME);
	if (!rt->win)
	{
		free(rt);
		mlx_destroy_display(rt->mlx);
		return (NULL);
	}
	return (rt);
}
