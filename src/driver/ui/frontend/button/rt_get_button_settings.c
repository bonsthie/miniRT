/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_button_settings.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:23:43 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/17 19:48:43 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__rt_button.h"
#include "htab.h"
#include "libft.h"
#include "rt_driver_button.h"
#include <stdio.h>
#include <sys/types.h>

uint32_t add_padding(uint16_t p1, uint16_t p2)
{
	uint32_t padding;

	padding = 0;
	if (p1 != 0xFFFF)
		padding += p1;
	if (p2 != 0xFFFF)
		padding += p2;
	return (padding);
}

void	button_default_size(struct s_rtss_button_settings *settings,
		t_button *button)
{
	int	size;
	int	char_width;
	int	font_pixel_height;

	char_width = 5;
	font_pixel_height = 16;
	size = ft_strlen(button->settings.text) * char_width;
	if (settings->width == 0xFFFFFFFF)
		settings->width = size + add_padding(settings->padding.left, settings->padding.right);
	if (settings->height == 0xFFFFFFFF)
		settings->height = font_pixel_height + add_padding(settings->padding.top, settings->padding.bottom);
	if (settings->border_size == 0xFFFFFFFF)
		settings->border_size = 0;
}

t_hentry	*__rtss_get_class_entry(const char *class, t_htab *tab)
{
	char	class_name[256];

	class_name[0] = '.';
	ft_strcpy(class_name + 1, (char *)class);
	return (htab_get(tab, class_name));
}

uint32_t	__rtss_get_color(t_htab *htab, t_hentry *hentry,
		enum e_button_action action)
{
	uint32_t	color;

	color = 0xFFFFFFFF;
	if (action == CLICK)
		color = hentry_get_spec(htab, hentry, (t_keyw)BACKGROUND_COLOR_CLIKED);
	else if (action == HOWEVER)
		color = hentry_get_spec(htab, hentry, (t_keyw)BACKGROUND_COLOR_HOWEVER);
	if (color != 0xFFFFFFFF)
		return (color);
	color = hentry_get_spec(htab, hentry, (t_keyw)BACKGROUND_COLOR);
	if (color != 0xFFFFFFFF)
		return (color);
	return (RT_BUTTON_COLOR);
}

struct s_rtss_button_settings	button_default_settings(t_button *button)
{
	struct s_rtss_button_settings	settings;
	t_hentry						*button_hentry;
	t_htab							*htab;

	htab = button->settings.htab;
	settings = (struct s_rtss_button_settings){0};
	button_hentry = htab_get(htab, "button");
	if (!button_hentry)
		return (settings);
	settings.color = __rtss_get_color(htab, button_hentry, button->action);
	settings.width = hentry_get_spec(htab, button_hentry, (t_keyw)WIDTH);
	settings.height = hentry_get_spec(htab, button_hentry, (t_keyw)HEIGHT);
	settings.margin.data = hentry_get_spec(htab, button_hentry, (t_keyw)MARGIN);
	settings.padding.data = hentry_get_spec(htab, button_hentry, (t_keyw)PADDING);
	settings.border_radius.data = hentry_get_spec(htab, button_hentry, (t_keyw)BORDER_RADIUS);
	settings.border_size = hentry_get_spec(htab, button_hentry, (t_keyw)BORDER_SIZE);
	settings.border_color = hentry_get_spec(htab, button_hentry, (t_keyw)BORDER_COLOR);
	return (settings);
}

struct s_rtss_button_settings	__button_class_to_settings(t_htab *htab,
		t_hentry *hentry, enum e_button_action action)
{
	struct s_rtss_button_settings	settings;

	settings.color = __rtss_get_color(htab, hentry, action);
	settings.width = hentry_get_spec(htab, hentry, (t_keyw)WIDTH);
	settings.height = hentry_get_spec(htab, hentry, (t_keyw)HEIGHT);
	settings.margin.data = hentry_get_spec(htab, hentry, (t_keyw)MARGIN);
	settings.padding.data = hentry_get_spec(htab, hentry, (t_keyw)PADDING);
	settings.border_radius.data = hentry_get_spec(htab, hentry, (t_keyw)BORDER_RADIUS);
	settings.border_size = hentry_get_spec(htab, hentry, (t_keyw)BORDER_SIZE);
	settings.border_color = hentry_get_spec(htab, hentry, (t_keyw)BORDER_COLOR);
	return (settings);
}

uint64_t	setting_merge_bitmask(uint64_t first, uint64_t second)
{
	uint16_t	tab[4];
	int			i;

	i = 3;
	while (i >= 0)
	{
		tab[i] = (uint16_t)(second & 0xFFFF);
		if (tab[i] == 0xFFFF)
			tab[i] = (uint16_t)(first & 0xFFFF);
		second >>= 16;
		first >>= 16;
		i--;
	}
	return ((uint64_t)tab[0] << 48) | ((uint64_t)tab[1] << 32) | ((uint64_t)tab[2] << 16) | ((uint64_t)tab[3]);
}

void	button_class_settings(struct s_rtss_button_settings *settings,
		t_button *button)
{
	struct s_rtss_button_settings	tmp;
	t_hentry						*hentry;
	t_htab							*htab;

	htab = button->settings.htab;
	hentry = __rtss_get_class_entry(button->settings.class, htab);
	if (!hentry)
		return ;
	tmp = __button_class_to_settings(button->settings.htab, hentry,
			button->action);
	if (tmp.color != 0xFFFFFFFF && tmp.color != RT_BUTTON_COLOR)
		settings->color = tmp.color;
	if (tmp.width != 0xFFFFFFFF)
		settings->width = tmp.width;
	if (tmp.height != 0xFFFFFFFF)
		settings->height = tmp.height;
	if (tmp.border_color != 0xFFFFFFFF)
		settings->border_color = tmp.border_color;
	if (tmp.border_size != 0xFFFFFFFF)
		settings->border_size = tmp.border_size;
	settings->border_radius.data = setting_merge_bitmask(settings->border_radius.data,
			tmp.border_radius.data);
	settings->padding.data = setting_merge_bitmask(settings->padding.data,
			tmp.padding.data);
	settings->margin.data = setting_merge_bitmask(settings->margin.data,
			tmp.margin.data);
}

struct s_rtss_button_settings	rt_get_button_settings(t_button *button)
{
	struct s_rtss_button_settings	settings;
	t_button_setting				*b_settings;

	settings = button_default_settings(button);
	b_settings = &button->settings;
	if (b_settings->class)
		button_class_settings(&settings, button);
	if (button->settings.style & TEXT)
	{
		printf("caca\n");
		button_default_size(&settings, button);
	}
	printf("button id %d\n\tcolor %#X\n\twidth %d height %d\n\tpadding %d %d %d %d\n\tmargin %d %d %d %d\n\tborder radius %d %d %d %d\n",
		button->settings.id, settings.color, settings.width, settings.height,
		settings.padding.left, settings.padding.bottom , settings.padding.right, settings.padding.top,
		settings.margin.left, settings.margin.bottom , settings.margin.right, settings.margin.top,
		settings.border_radius.top_left, settings.border_radius.top_right , settings.border_radius.bottom_right, settings.border_radius.bottom_left);
	/* printf("[width] %u\n", settings.width); */
	return (settings);
}
