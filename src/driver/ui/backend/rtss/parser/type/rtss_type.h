/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_type.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:06:04 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/10 15:57:56 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTSS_TYPE_H
# define RTSS_TYPE_H

# include "htab.h"

// repete code is on purpose
// need codegen for what i want to do but norminette issue
// i now i could make general rules

// size
void	rtss_type_width(t_htab *tab, t_hentry *entry, char *value);
void	rtss_type_height(t_htab *tab, t_hentry *entry, char *value);

// color
void	rtss_type_background_color(t_htab *tab, t_hentry *entry, char *value);
void	rtss_type_background_color_however(t_htab *tab, t_hentry *entry,
			char *value);
void	rtss_type_background_color_click(t_htab *tab, t_hentry *entry,
			char *value);

// margin
void	rtss_type_margin(t_htab *tab, t_hentry *entry, char *value);
void	rtss_type_margin_left(t_htab *tab, t_hentry *entry, char *value);
void	rtss_type_margin_right(t_htab *tab, t_hentry *entry, char *value);
void	rtss_type_margin_top(t_htab *tab, t_hentry *entry, char *value);
void	rtss_type_margin_bottom(t_htab *tab, t_hentry *entry, char *value);

// padding
void	rtss_type_padding(t_htab *tab, t_hentry *entry, char *value);
void	rtss_type_padding_left(t_htab *tab, t_hentry *entry, char *value);
void	rtss_type_padding_right(t_htab *tab, t_hentry *entry, char *value);
void	rtss_type_padding_top(t_htab *tab, t_hentry *entry, char *value);
void	rtss_type_padding_bottom(t_htab *tab, t_hentry *entry, char *value);

// border_radius
void	rtss_type_border_radius(t_htab *tab, t_hentry *entry, char *value);
void	rtss_type_border_radius_top_left(t_htab *tab, t_hentry *entry,
			char *value);
void	rtss_type_border_radius_top_right(t_htab *tab, t_hentry *entry,
			char *value);
void	rtss_type_border_radius_bottom_right(t_htab *tab, t_hentry *entry,
			char *value);
void	rtss_type_border_radius_bottom_left(t_htab *tab, t_hentry *entry,
			char *value);

#endif /* RTSS_TYPE_H */
