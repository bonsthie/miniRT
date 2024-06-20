#include "../_hook.h"
#include "rt_driver.h"
#include <stdlib.h>
#include <object.h>

void however_to_click(t_screen *screen, t_button *button)
{
	while (button)
	{
		if (button->action == HOWEVER)
		{
			button->action = CLICK;
			rt_print_button(screen);
			return ;
		}
		button = button->next;
	}
}

void mousedown_hook_top_bar(int key, t_screen *screen)
{
	if (key == MOUSE_LEFT)
		however_to_click(screen, screen->button_top);
	/* rt_print_button(screen); */

}

void mousedown_hook_side_bar(int key, t_mlx *mlx)
{
	(void)mlx;
	(void)key;
}

void change_obj_color(t_object *object, int id)
{
	if (!object || id == 0)
		return ;
	while (object->id != id)
		object = object->next;
	union u_color color;

	color.value = 0xFFFFFFFF;
	color.components.red = rand() % 255;
	update_color_object(object->object, color.value);
}

void mousedown_hook_scene(int key, t_mlx *mlx)
{
	if (key == MOUSE_LEFT)
	{
		change_obj_color(mlx->scene->object, mlx->img->obj_id[mlx->screen->mouse_y][mlx->screen->mouse_x]);
	}
}

int mousedown_hook(int key, void *data)
{
	t_mlx *mlx;
	t_screen *screen;

	mlx = data;
	screen = mlx->screen;
	if (screen->mouse_y <= RT_UI_TOP_BAR)
		mousedown_hook_top_bar(key, screen);
	else if (screen->mouse_x >= RT_WIDTH + RT_UI_SIDE_BAR)
		mousedown_hook_side_bar(key, mlx);
	else
		mousedown_hook_scene(key, mlx);
		
	return (0);

}
