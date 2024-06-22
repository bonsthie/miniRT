/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousewheel_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:13:03 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/22 17:55:05 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_hook.h"
#include <stdio.h>

int mousewheel_hook(int key, void *data)
{
	struct s_hook_data *hdata;

	printf("%d\n", key);
	hdata = data;
	(void)hdata;
	return (0);
}
