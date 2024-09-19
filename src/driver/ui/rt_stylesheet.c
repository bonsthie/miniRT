/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_stylesheet.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:31:39 by babonnet          #+#    #+#             */
/*   Updated: 2024/09/19 15:38:52 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <htab.h>
#include <stdlib.h>
#include "backend/rtss/rtss.h"
#include "libft.h"

t_htab *rt_create_stylesheet(const char *filename)
{
	size_t size;

	size = ft_strlen(filename);
	if (size < 5)
		return (NULL);
	if (ft_strcmp(filename + size - 5, ".rtss"))
	{
		ft_putstr_fd("RT: Error wrong file rtss file formats\n", 2);
		return (NULL);
	}
	return (rtss_interpreter(filename));
}

void	rt_destroy_stylesheet(t_htab *htab)
{
	htab_del(htab);
	free(htab);
}
