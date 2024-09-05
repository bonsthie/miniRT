/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:58:44 by babonnet          #+#    #+#             */
/*   Updated: 2024/07/18 13:48:58 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;
	char		*dest;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	if (end == 0)
		return (ft_strdup(""));
	while (end > 0 && ft_strchr(set, s1[end - 1]))
		--end;
	while (start < end && ft_strchr(set, s1[start]) && s1[start])
		start++;
	if (start > end)
		return (ft_strdup(""));
	dest = malloc((end - start + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &s1[start], end - start + 1);
	return (dest);
}
