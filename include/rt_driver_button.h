/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_driver_button.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:40:39 by bonsthie          #+#    #+#             */
/*   Updated: 2024/08/27 17:20:23 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_DRIVER_BUTTON_H
# define RT_DRIVER_BUTTON_H

# include "rt_driver.h"
# include <stdint.h>

struct s_padding {
	uint8_t	top;
	uint8_t	bottom;
	uint8_t	left;
	uint8_t	right;
};

enum				e_ui_style
{
	BUTTON,
	DISPLAY_INT,
	DISPLAY_FLOAT,
	BENTO
};

typedef struct s_ui_groups
{
	uint8_t			style_ui;
	void			*next;
}					t_ui_groups;

/**
 * BUTTON ACTION
 */

/**
 * @enum e_button_style
 * @brief Enum for button styles; can be combined using a bitwise OR
 */

enum				e_button_style
{
	TEXT = 1u << 1,
	IMAGE = 1u << 0,
};

# define RT_SIMPLE_BUTTON -1

/**
 * @struct s_button_setting
 * @brief Structure to hold button settings
 *
 * Use RT_SIMPLE_BUTTON for the action to end when the button is unpressed.
 */
typedef struct s_button_setting
{
	uint8_t				style_ui;
	t_ui_groups			*next;

	uint8_t				style;
	uint8_t				id;
	uint8_t				on_start : 1;

	uint16_t			width;
	uint16_t			height;

	struct s_padding	padding;
	struct s_padding	margin;

	void				*data;
	void				(*f)(void *);

	char				*text;
	void				*image; // not implemented for now

}					t_button_setting;

/**
 * BENTO ACTION
 */

typedef struct s_bento_setting
{
	uint8_t			style;
	t_ui_groups		*next;

	char			*text_left;
	void			*image; // not implemented for now

}					t_bento_setting;

typedef struct s_rt_ui
{
	uint8_t			group_style;

	uint16_t		width;
	uint16_t		heigh;

	t_ui_groups		*element;
	struct t_rt_ui	*next;

}					t_rt_ui;

/**
 * @brief Add a text button to the top of the screen
 *
 * @param screen   Pointer to the screen structure
 * @param settings Button settings
 */
void				rt_add_text_button_top(t_screen *screen,
						t_button_setting settings);

#endif // RT_DRIVER_BUTTON_H
