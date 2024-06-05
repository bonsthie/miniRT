#include "../_rt_mlx.h"
#include "rt_driver.h"

void	reset_however_button(t_screen *screen)
{
	t_button	*button;

	button = screen->button_top;
	while (button)
	{
		if (button->action == HOWEVER)
			button->action = SLEEP;
		button = button->next;
	}
	button = screen->button_side;
	while (button)
	{
		if (button->action == HOWEVER)
			button->action = SLEEP;
		button = button->next;
	}
}
