#include "../_hook.h"
#include "rt_driver.h"

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

int mousedown_hook(int key, void *data)
{
	t_screen *screen;

	screen = data;
	if (screen->mouse_y <= RT_UI_TOP_BAR)
		mousedown_hook_top_bar(key, screen);
		
	return (0);

}
