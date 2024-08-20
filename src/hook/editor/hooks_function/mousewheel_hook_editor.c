/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousewheel_hook_editor.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:13:03 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/20 14:32:14 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../_hook.h"
#include <stdio.h>

int mousewheel_hook_editor(int key, void *data)
{
	struct s_hook_data *hdata;

	printf("%d\n", key);
	hdata = data;
	(void)hdata;
	return (0);
}
