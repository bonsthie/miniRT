/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _hook.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:10:56 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/19 16:24:36 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _HOOK_H
# define _HOOK_H

# include "../../_rt_mlx.h"
# include "rt_mesh_obj.h"
# include <stdbool.h>

int		rt_window_hook(int event, void *param);
int		rt_mousedown_hook(int key, void *data);
int		rt_mouseup_hook(int key, void *data);
int		rt_keyup_hook(int key, void *data);
int		rt_mousewheel_hook(int key, void *data);

enum	e_keycode
{
	NONE,
	MOUSE_LEFT,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,
	A_KEY,
	B_KEY,
	C_KEY,
	D_KEY,
	E_KEY,
	F_KEY,
	G_KEY,
	H_KEY,
	I_KEY,
	J_KEY,
	K_KEY,
	L_KEY,
	M_KEY,
	N_KEY,
	O_KEY,
	P_KEY,
	Q_KEY,
	R_KEY,
	S_KEY,
	T_KEY,
	U_KEY,
	V_KEY,
	W_KEY,
	X_KEY,
	Y_KEY,
	Z_KEY,
	N1_KEY,
	N2_KEY,
	N3_KEY,
	N4_KEY,
	N5_KEY,
	N6_KEY,
	N7_KEY,
	N8_KEY,
	N9_KEY,
	N0_KEY,
	ENTER_KEY,
	ESCAPE,
	BACKSPACE,
	TAB_KEY,
	SPACE_KEY,
	MINUS_KEY,
	EQUAL_KEY,
	LEFT_BRACKET,
	RIGHT_BRACKET,
	BACKSLASH,
	SEMICOLON,
	APOSTROPHE,
	GRAVE,
	COMMA,
	PERIOD,
	SLASH,
	CAPS_LOCK,
	F1_KEY,
	F2_KEY,
	F3_KEY,
	F4_KEY,
	F5_KEY,
	F6_KEY,
	F7_KEY,
	F8_KEY,
	F9_KEY,
	F10_KEY,
	F11_KEY,
	F12_KEY,
	PRINT_SCREEN,
	SCROLL_LOCK,
	PAUSE_KEY,
	INSERT_KEY,
	HOME_KEY,
	PAGE_UP,
	DELETE_KEY,
	END_KEY,
	PAGE_DOWN,
	L_ARROW,
	R_ARROW,
	UP_ARROW,
	DOWN_ARROW,
	NUM_LOCK,
	KP_DIVIDE,
	KP_MULTIPLY,
	KP_MINUS,
	KP_PLUS,
	KP_ENTER,
	KP_1,
	KP_2,
	KP_3,
	KP_4,
	KP_5,
	KP_6,
	KP_7,
	KP_8,
	KP_9,
	KP_0,
	KP_DOT,
	NON_US_BACKSLASH,
	APPLICATION,
	POWER_KEY,
	KP_EQUAL,
	F13_KEY,
	F14_KEY,
	F15_KEY,
	F16_KEY,
	F17_KEY,
	F18_KEY,
	F19_KEY,
	F20_KEY,
	F21_KEY,
	F22_KEY,
	F23_KEY,
	F24_KEY,
	L_CTRL,
	L_SHIFT,
	L_ALT,
	L_GUI,
	R_CTRL,
	R_SHIFT,
	R_ALT,
	R_GUI,
	MOUSE_BUTTON_4,
	MOUSE_BUTTON_5
};

#endif
