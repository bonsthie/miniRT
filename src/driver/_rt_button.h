/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _rt_button.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:37:27 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/19 16:24:35 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RT_BUTTON_H
# define _RT_BUTTON_H

# include "rt_driver.h"

typedef						void(t_button_func)(void *data);

enum						e_button_type
{
	IMG,
	TXT,
	SEPARATOR,
};

enum						e_button_action
{
	SLEEP,
	HOWEVER,
	CLICK
};

# define TXT_BUTTON_SIDE 40

# define RT_BUTTON_SIDE_PADDING 10
# define RT_BUTTON_COLOR 0xFFFFFF00
# define RT_BUTTON_COLOR_HOWEVER 0xFFFF0000
# define RT_BUTTON_COLOR_CLICK 0xFFFFFFFF

typedef struct s_button
{
	struct s_button_setting	settings;
	enum e_button_action	action;
	struct s_button			*next;
}							t_button;

void						reset_however_button(t_screen *screen);
void						rt_print_button(t_screen *screen);
void						rt_update_ui(t_screen *screen);

#endif
