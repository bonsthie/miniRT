#include "../_hook.h"
#include "rt_driver.h"
#include <stdio.h>

void click_to_however(t_button *button)
{
	while (button)
	{
		if (button->action == CLICK)
		{
			button->action = HOWEVER;
			return ;
		}
		button = button->next;
	}
}

void mouseup_hook_top_bar(int key, t_screen *screen)
{
	if (key == MOUSE_LEFT)
		click_to_however(screen->button_top);

}

int mouseup_hook(int key, void *data)
{
	t_screen *screen;

	screen = data;
	mouseup_hook_top_bar(key, screen);
		
	return (0);

}
