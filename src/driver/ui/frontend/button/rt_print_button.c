/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_button.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:38:57 by babonnet          #+#    #+#             */
/*   Updated: 2024/09/17 20:05:31 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__rt_button.h"
#include "mlx.h"
#include "rt_driver.h"

int is_pixel_in_border_radius(int x, int y, struct s_rtss_button_settings settings, int x0, int y0)
{
    int x1 = x0 + settings.width + settings.padding.left + settings.padding.right;
    int y1 = y0 + settings.height;
    int border_width = 1; // Border width in pixels

    // Check if the pixel is outside the button bounds
    if (x < x0 || x >= x1 || y < y0 || y >= y1)
        return 0; // Outside

    uint16_t radius_tl = settings.border_radius.top_left;
    uint16_t radius_tr = settings.border_radius.top_right;
    uint16_t radius_bl = settings.border_radius.bottom_left;
    uint16_t radius_br = settings.border_radius.bottom_right;

    if (x < x0 + radius_tl && y < y0 + radius_tl)
    {
        int dx = x - (x0 + radius_tl - 1);
        int dy = y - (y0 + radius_tl - 1);
        int dist_sq = dx * dx + dy * dy;

        int outer_radius_sq = radius_tl * radius_tl;
        int inner_radius_sq = (radius_tl - border_width) * (radius_tl - border_width);

        if (dist_sq > outer_radius_sq)
            return 0;
        else if (settings.border_size && dist_sq >= inner_radius_sq)
            return 2;
        else
            return 1;
    }
    else if (x >= x1 - radius_tr && y < y0 + radius_tr)
    {
        int dx = x - (x1 - radius_tr);
        int dy = y - (y0 + radius_tr - 1);
        int dist_sq = dx * dx + dy * dy;

        int outer_radius_sq = radius_tr * radius_tr;
        int inner_radius_sq = (radius_tr - border_width) * (radius_tr - border_width);

        if (dist_sq > outer_radius_sq)
            return 0;
        else if (settings.border_size && dist_sq >= inner_radius_sq)
            return 2;
        else
            return 1;
    }
    // Bottom-left corner
    else if (x < x0 + radius_bl && y >= y1 - radius_bl)
    {
        int dx = x - (x0 + radius_bl - 1);
        int dy = y - (y1 - radius_bl);
        int dist_sq = dx * dx + dy * dy;

        int outer_radius_sq = radius_bl * radius_bl;
        int inner_radius_sq = (radius_bl - border_width) * (radius_bl - border_width);

        if (dist_sq > outer_radius_sq)
            return 0;
        else if (settings.border_size && dist_sq >= inner_radius_sq)
            return 2;
        else
            return 1;
    }
    // Bottom-right corner
    else if (x >= x1 - radius_br && y >= y1 - radius_br)
    {
        int dx = x - (x1 - radius_br);
        int dy = y - (y1 - radius_br);
        int dist_sq = dx * dx + dy * dy;

        int outer_radius_sq = radius_br * radius_br;
        int inner_radius_sq = (radius_br - border_width) * (radius_br - border_width);

        if (dist_sq > outer_radius_sq)
            return 0;
        else if (settings.border_size && dist_sq >= inner_radius_sq)
            return 2;
        else
            return 1;
    }
    else if (settings.border_size)
    {
        if (x < x0 + border_width || x >= x1 - border_width)
            return 2;
        if (y < y0 + border_width || y >= y1 - border_width)
            return 2;
    }
	return 1;
}

void print_button_top_txt(t_screen *screen, t_button *button_top, int *pixel_padding)
{
    uint32_t                        x;
    uint32_t                        y;
    uint32_t                        button_size_width;
    struct s_rtss_button_settings          settings;
    int                             x0;
    int                             y0;

    settings = rt_get_button_settings(button_top);
    y0 = settings.margin.top;
    *pixel_padding += settings.margin.left;
	x0 = *pixel_padding;
    button_size_width = settings.width + settings.padding.left + settings.padding.right;

    y = y0;
    while (y < y0 + settings.height)
    {
        x = x0;
        while (x < x0 + button_size_width)
        {
            int pixel_status = is_pixel_in_border_radius(x, y, settings, x0, y0);
            if (pixel_status == 1)
                mlx_pixel_put(screen->mlx, screen->win, x, y, settings.color);
            else if (pixel_status == 2)
                mlx_pixel_put(screen->mlx, screen->win, x, y, settings.border_color);
            x++;
        }
        y++;
    }
    *pixel_padding += settings.margin.left;
    mlx_string_put(screen->mlx, screen->win, *pixel_padding + settings.padding.left,
        y0 + settings.padding.top + 13, 0xFF000000, button_top->settings.text);
    *pixel_padding += button_size_width + settings.margin.right;
}

void	rt_print_button(t_screen *screen)
{
	t_button		*button_top;
	int				pixel_padding;

	if (!screen)
		return ;
	button_top = screen->button_top;
	if (!button_top)
		return ;
	pixel_padding = 0;
	while (button_top)
	{
			print_button_top_txt(screen, button_top, &pixel_padding);
		button_top = button_top->next;
	}
}
